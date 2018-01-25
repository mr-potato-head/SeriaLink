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
#include "src/terminalportview.h"
#include "src/dumpportview.h"
#include "src/tableportview.h"

Session::Session(QObject *parent)
  : QObject(parent) {
}

Session::~Session() {
//  // Delete threads for this session
//  QList<QThread*>::iterator itBeginTh = thread_list_.begin();
//  QList<QThread*>::iterator itEndTh = thread_list_.end();
//  for (QList<QThread*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
//    (*it)->quit();
//    if (!(*it)->wait(1000)) {
//      qDebug() << "Timeout arret du thread.";
//    }
//    delete *it;
//  }

//  // Delete COM ports for this session
//  QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
//  QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
//  QList<ComPortManager*>::iterator it = itBeginPort;
//  for (; it != itEndPort ; it++) {
//    delete *it;
//  }
}

void Session::SetTopbar(TopBar* top_bar) {
  top_bar_ = top_bar;
}

void Session::SetPageContainer(PageContainer* page_container) {
  page_container_ = page_container;
}

void Session::Close() {
  foreach (PortPage* port_page, page_list_) {
    delete port_page;
  }
}

void Session::AddPage(void) {
  // Create page
  PortPage* page = new PortPage(this, page_list_.size());
  page_list_.append(page);

  // Add page in container
  quint8 page_index = page_container_->addWidget(page);
  page_container_->setCurrentIndex(page_index);

  // Update topbar widgets
  //emit PageAdded(page_index);
  top_bar_->AddPageButton();

  // Update current page index in session
  this->SetCurrentPageIndex(page_index);
}

void Session::AddPage(ComPortSettings* port_settings) {
  // Create page
  PortPage* page = new PortPage(this, page_list_.size());
  page_list_.append(page);

  // Add page in container
  quint8 page_index = page_container_->addWidget(page);
  page_container_->setCurrentIndex(page_index);

  // Add port in page
  page->AddPort(port_settings);

  // Emit signal to update topbar widgets
  //emit PageAdded(page_index);
  // Update topbar widgets
  top_bar_->AddPageButton();
  top_bar_->UpdatePageButtonName(page_index);

  // Update current page index in session
  this->SetCurrentPageIndex(page_index);
}

void Session::DeletePage(quint8 page_idx) {
  int old_last_idx = page_list_.size()-1;

  PortPage* port_page = page_list_.at(page_idx);
  page_container_->removeWidget(port_page);
  delete port_page;
  page_list_.removeAt(page_idx);

  int index = 0;
  foreach (PortPage* port_page, page_list_) {
    port_page->SetPageIndex(index);
  }

  if(page_idx == 0) {
    this->SetCurrentPageIndex(0);
  } else if (page_idx == old_last_idx) {
    this->SetCurrentPageIndex(page_list_.size()-1);
  } else {
    this->SetCurrentPageIndex(page_idx);
  }

  top_bar_->DeletePageButton(page_idx);
}

void Session::AddPort(quint8 page_idx, ComPortSettings* port_settings) {

  PortPage* page = page_list_.at(page_idx);

  // Add port in page
  page->AddPort(port_settings);

  top_bar_->UpdatePageButtonName(page_idx);
//  // Create new port manager
//  ComPortManager* com_port_mgr = new ComPortManager(port_settings);
//  com_port_mgr_list_.append(com_port_mgr);

//  // Create thread for this port manager
//  QThread* thread = new QThread(this);
//  thread_list_.append(thread);
//  com_port_mgr->moveToThread(thread);
//  thread->start(QThread::TimeCriticalPriority);

//  // Create page
//  PortPage* page = new PortPage(this, page_idx);
//  page->AddPortMgr(com_port_mgr);
//  page_list_.append(page);
//  int page_index = page_container_->addWidget(page);
//  page_container_->setCurrentIndex(page_index);

//  current_port_mgr_index_ = page_idx;
//  emit PortAdded(current_port_mgr_index_);
}

void Session::AddPort(quint8 page_idx, const QJsonObject& port_object) {
  ComPortSettings* port_settings = new ComPortSettings();
  port_settings->SetBaudRate(
        static_cast<QSerialPort::BaudRate>(
          port_object["port_baudrate"].toInt()));
  port_settings->SetDataBits(
        static_cast<QSerialPort::DataBits>(
          port_object["port_data_bits"].toInt()));
  port_settings->SetFlowControl(
        static_cast<QSerialPort::FlowControl>(
          port_object["port_flow_ctrl"].toInt()));
  port_settings->SetParity(
        static_cast<QSerialPort::Parity>(
          port_object["port_parity"].toInt()));
  QSerialPortInfo port_info(port_object["port_name"].toString());
  port_settings->SetPortInfo(port_info);
  port_settings->SetStopBits(
        static_cast<QSerialPort::StopBits>(
          port_object["port_stop_bits"].toInt()));

  // Call overloaded AddPort function
  this->AddPort(page_idx, port_settings);
}

void Session::UpdatePortSettings(quint8 page_idx,
                        quint8 port_idx,
                        ComPortSettings* port_settings) {

}

void Session::DeletePort(quint8 page_idx, quint8 port_idx) {
  page_list_.at(page_idx)->DeletePort(port_idx);
}

void Session::AddView(quint8 page_idx, ViewSettings* settings) {
//  PortView* view;
//  switch (settings->GetViewType()) {
//  case ViewSettings::ViewType::kDump:
//    view = new DumpPortView(settings);
//    break;
//  case ViewSettings::ViewType::kTerminal:
//    view = new TerminalPortView(settings);
//    break;
//  case ViewSettings::ViewType::kTable:
//    view = new TablePortView(settings);
//    break;
//  default:
//    break;
//  }

//  ComPortManager* port_mgr = com_port_mgr_list_.at(page_idx);

//  // Connect received data to port
//  connect(port_mgr, SIGNAL(Receive(DataPacket const&)),
//          view, SLOT(OnReceivedData(DataPacket const&)));
  page_list_.at(page_idx)->AddView(settings);
}

void Session::AddView(quint8 page_idx, const QJsonObject& view_object) {
  ViewSettings* settings = new ViewSettings(view_object);
  this->AddView(page_idx, settings);
}

void Session::UpdateViewSettings(quint8 page_idx,
                                 quint8 view_idx,
                                 ViewSettings *settings) {

}

void Session::DeleteView(quint8 page_idx, quint8 view_idx) {
  //page_list_.at(page_idx)->GetViewList()->removeAt(view_idx);
}

void Session::SetCurrentPageIndex(int page_index) {
  current_page_index_ = page_index;
  top_bar_->UpdateSelectorButtonStatus();
  top_bar_->UpdateSwitcherButtonStatus();
  page_container_->setCurrentIndex(page_index);
}

//void Session::OpenPort(qint32 index) {
//  ComPortManager* port_mgr = com_port_mgr_list_.at(index);
//  QTimer::singleShot(0, port_mgr, &ComPortManager::OpenPort);
//}

//void Session::ClosePort(qint32 index) {
//  ComPortManager* port_mgr = com_port_mgr_list_.at(index);
//  QTimer::singleShot(0, port_mgr, &ComPortManager::ClosePort);
//}

//quint8 Session::GetPortNumber(void) {
//  return com_port_mgr_list_.size();
//}

quint8 Session::GetCurrentPageIndex(void) {
  return current_page_index_;
}

//ComPortManager* Session::GetPortManager(qint32 index) {
//  return com_port_mgr_list_.at(index);
//}

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
          // Create page
          this->AddPage();

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
            this->AddView(page_idx, view_object);
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
  QFile session_file(filepath);

  if (!session_file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QJsonArray page_array;
  for (int i=0 ; i < page_list_.size() ; i++) {
    QJsonObject page_object;
    // Create ports
    QJsonArray port_array;
    for (int j=0 ; j < page_list_.at(i)->GetPortMgrList()->size() ; j++) {
      QList<ComPortManager*>* port_mgr = page_list_.at(i)->GetPortMgrList();
      ComPortSettings* settings = port_mgr->at(j)->GetPortSettings();
      QJsonObject port_object = settings->ToJson();
      port_array.append(port_object);
    }

    // Create views
    QJsonArray view_array;
    QList<PortView*>* port_view_list = page_list_.at(i)->GetViewList();
    for (int k=0 ; k < port_view_list->size() ; k++) {
      ViewSettings* settings = port_view_list->at(k)->GetViewSettings();
      QJsonObject view_object = settings->ToJson();
      view_array.append(view_object);
    }

    page_object["page_ports"] = port_array;
    page_object["page_views"] = view_array;
    page_array.append(page_object);
  }

  QJsonObject session_object;
  session_object.insert("session_pages", page_array);

  QJsonDocument save_doc(session_object);
  session_file.write(save_doc.toJson());
  session_file.close();
}

QList<PortPage*>* Session::GetPortPageList(void) {
  return &page_list_;
}
