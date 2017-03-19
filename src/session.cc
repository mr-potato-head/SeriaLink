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
  // Create new port manager
  ComPortManager* com_port_mgr = new ComPortManager(port_settings);
  com_port_mgr_list_.append(com_port_mgr);

  // Create thread for this port manager
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  com_port_mgr->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  current_port_mgr_index_ = com_port_mgr_list_.size()-1;
  emit PortAdded(current_port_mgr_index_);
}

void Session::AddPort(const QJsonObject& port_object) {
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
  this->AddPort(&port_settings);
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

void Session::LoadPortsFromJson(const QJsonArray& session_pages) {

}
