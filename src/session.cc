/*
 * Copyright (C) 2016 Guilhem GUYONNET
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "src/session.h"

Session::Session(QObject *parent)
  : QObject(parent) {
}

Session::~Session() {
    // Delete threads for this session
    QList<QThread*>::iterator itBeginTh = thread_list_.begin();
    QList<QThread*>::iterator itEndTh = thread_list_.end();
    for (QList<QThread*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
        (*it)->quit();
        if (!(*it)->wait(1000)) {
            qDebug() << "Timeout arret du thread.";
        }
        delete *it;
    }

    // Delete COM ports for this session
    QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
    QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
    QList<ComPortManager*>::iterator it = itBeginPort;
    for (; it != itEndPort ; it++) {
      delete *it;
    }
}

void Session::Close() {
  // Delete COM ports for this session
  QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
  QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
  QList<ComPortManager*>::iterator it = itBeginPort;
  for (; it != itEndPort ; it++) {
    QTimer::singleShot(0, *it, &ComPortManager::ClosePort);
  }
}

void Session::AddPort(ComPortSettings* port_settings) {
  this->AddPort(current_port_mgr_index_, port_settings);
}

void Session::AddPort(qint8 page_idx, ComPortSettings* port_settings) {
  // Create new port manager
  ComPortManager* com_port_mgr = new ComPortManager(port_settings);
  com_port_mgr_list_.append(com_port_mgr);
  Page* page = new Page();
  page->port_setting_list_.append(port_settings);
  page_list_.append(page);

  // Create thread for this port manager
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  com_port_mgr->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  current_port_mgr_index_ = com_port_mgr_list_.size()-1;
  emit PortAdded(current_port_mgr_index_);
}

void Session::AddPort(qint8 page_idx, const QJsonObject& port_object) {
  ComPortSettings port_settings;
  port_settings.SetBaudRate(
        static_cast<QSerialPort::BaudRate>(
          port_object["port_baudrate"].toInt()));
  port_settings.SetDataBits(
        static_cast<QSerialPort::DataBits>(
          port_object["port_data_bits"].toInt()));
  port_settings.SetFlowControl(
        static_cast<QSerialPort::FlowControl>(
          port_object["port_flow_ctrl"].toInt()));
  port_settings.SetParity(
        static_cast<QSerialPort::Parity>(
          port_object["port_parity"].toInt()));
  QSerialPortInfo port_info(port_object["port_name"].toString());
  port_settings.SetPortInfo(port_info);
  port_settings.SetStopBits(
        static_cast<QSerialPort::StopBits>(
          port_object["port_stop_bits"].toInt()));

  // Call overloaded AddPort function
  this->AddPort(page_idx, &port_settings);
}

void AddView(qint8 page_idx, ViewSettings* view_settings) {

}

void AddView(qint8 page_idx, const QJsonObject& view_object) {

}

void Session::SetCurrentPortMgrIndex(qint32 index) {
  current_port_mgr_index_ = index;
  emit IndexChanged(index);
}

void Session::OpenPort(qint32 index) {
  ComPortManager* port_mgr = com_port_mgr_list_.at(index);
  QTimer::singleShot(0, port_mgr, &ComPortManager::OpenPort);
}

void Session::ClosePort(qint32 index) {
    ComPortManager* port_mgr = com_port_mgr_list_.at(index);
    QTimer::singleShot(0, port_mgr, &ComPortManager::ClosePort);
}

quint8 Session::GetPortNumber(void) {
  return com_port_mgr_list_.size();
}

quint8 Session::GetCurrentPortMgrIndex(void) {
  return current_port_mgr_index_;
}

ComPortManager* Session::GetPortManager(qint32 index) {
    return com_port_mgr_list_.at(index);
}

void Session::LoadFromFile(QString filepath) {
  QFile session_file(filepath);

  if (!session_file.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QByteArray json_data = session_file.readAll();
  QJsonDocument load_doc(QJsonDocument::fromJson(json_data));

  if (!load_doc.isNull()) {
    if (load_doc.isObject()) {
      // Pass JSON data session
      QJsonObject global_object = load_doc.object();
      if (global_object["session_pages"].isArray()) {
        QJsonArray session_pages = global_object["session_pages"].toArray();
        for (int page_idx = 0; page_idx < session_pages.size(); ++page_idx) {
          QJsonObject page_object = session_pages[page_idx].toObject();
          // Add ports in session
          QJsonArray port_array = page_object["page_ports"].toArray();
          for (int port_idx = 0; port_idx < port_array.size(); ++port_idx) {
            QJsonObject port_object = port_array[port_idx].toObject();
            this->AddPort(page_idx, port_object);
          }

          // Add ports in session
          QJsonArray view_array = page_object["page_views"].toArray();
          for (int view_idx = 0; view_idx < view_array.size(); ++view_idx) {
            QJsonObject view_object = view_array[view_idx].toObject();
            ViewSettings* settings = new ViewSettings(view_object);
            page_list_.at(page_idx)->view_setting_list_.append(settings);
            emit ViewAdded(page_idx, settings);
          }
        }
      } else {
        qWarning("session_pages is not and array.");
      }
    } else {
      qWarning("Can't find JSON object in file.");
    }
  } else {
    qWarning("Can't parse session file.");
  }
}

void Session::SaveInFile(QString filepath) {

}

