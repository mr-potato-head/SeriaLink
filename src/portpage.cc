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

#include "src/portpage.h"
#include "src/session.h"
#include "src/addormodifyportdialog.h"
#include "src/terminalportview.h"
#include "src/dumpportview.h"
#include "src/tableportview.h"

PortPage::PortPage(Session* session,
                   quint32 page_index,
                   QWidget* parent)
  : QWidget(parent),
    session_(session),
    page_index_{page_index} {
  //port_info_ = new PortInfoWidget(&port_mgr_list_, this);
  port_info_area_widget_ = new PortInfoAreaWidget(session, page_index, this);
  send_widget_ = new SendWidget(&port_mgr_list_, this);
  view_widget_ = new QWidget(this);
  view_layout_ = new QHBoxLayout(view_widget_);

//  connect(port_info_, SIGNAL(NewViewClicked()),
//          this, SLOT(OnNewViewClicked()));
//  connect(port_info_, SIGNAL(NewPortClicked()),
//          this, SLOT(OnNewPortClicked()));

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(port_info_area_widget_, 0, 0);
  main_layout_->addWidget(view_widget_, 0, 1);
  main_layout_->addWidget(send_widget_, 1, 0, 1, 2);

  main_layout_->setColumnStretch(0, 20);
  main_layout_->setColumnStretch(1, 80);
  main_layout_->setRowStretch(0, 80);
}

PortPage::~PortPage() {
  //  // Delete COM ports for this session
  //  QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
  //  QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
  //  QList<ComPortManager*>::iterator it = itBeginPort;
  //  for (; it != itEndPort ; it++) {
  //    QTimer::singleShot(0, *it, &ComPortManager::ClosePort);
  //  }

  // Delete threads
  foreach (QThread* thread, thread_list_) {
    thread->quit();
    if (!thread->wait(1000)) {
      qDebug() << "Timeout arret du thread.";
    }
    delete thread;
  }

  // Delete port managers
  foreach (ComPortManager* port_mgr, port_mgr_list_) {
    delete port_mgr;
  }

  // Delete views
  foreach (PortView* port_view, view_list_) {
    delete port_view;
  }


}

void PortPage::OnNewViewClicked(void) {
  ViewSettings* view_settings = new ViewSettings();
  ViewSettingDialog view_setting_dialog(view_settings,
                                        ViewSettingDialog::ActionType::kAdd,
                                        this);
  qint32 result = view_setting_dialog.exec();

  switch (result) {
  case QDialog::Accepted:
  {
    session_->AddView(page_index_, view_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::OnNewPortClicked(void) {
  ComPortSettings* port_settings = new ComPortSettings();
  AddOrModifyPortDialog addDialog(port_settings, AddOrModifyPortDialog::ActionType::kAdd, this);
  qint32 result = addDialog.exec();

  switch (result) {
  case QDialog::Accepted:
  {
    session_->AddPort(page_index_, port_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::AddView(ViewSettings* settings) {


  //  view_layout_->addWidget(view);
  //  view_list_.append(view);

  //  connect(view, &PortView::DeleteView, [=](PortView* view) {
  //    for (int i=0 ; i < view_list_.size() ; i++) {
  //      if (view_list_.at(i) == view) {
  //        delete view;
  //        view_list_.removeAt(i);
  //      }
  //    }
  //  });

  PortView* view;
  switch (settings->GetViewType()) {
  case ViewSettings::ViewType::kDump:
    view = new DumpPortView(settings, this);
    break;
  case ViewSettings::ViewType::kTerminal:
    view = new TerminalPortView(settings, this);
    break;
  case ViewSettings::ViewType::kTable:
    view = new TablePortView(settings, this);
    break;
  default:
    break;
  }
  view_layout_->addWidget(view);
  view_list_.append(view);

  // Connect port managers to this new view
  foreach (ComPortManager* port_mgr, port_mgr_list_) {
    connect(port_mgr, SIGNAL(DataReceived(DataPacket const&)),
            view, SLOT(OnReceivedData(DataPacket const&)));
    connect(port_mgr, SIGNAL(DataSent(DataPacket const&)),
            view, SLOT(OnDataSent(DataPacket const&)));
  }

  // Process DeleteView signal
  connect(view, &PortView::DeleteView, [=](PortView* view) {

    int view_idx = view_list_.indexOf(view);
    view_list_.removeAt(view_idx);
    delete view;

//    for (int i=0 ; i<view_list_.size() ; i++) {
//      if (view_list_.at(i) == view) {
//        delete view;
//        session_->DeleteView(port_index_, i);
//      }
//    }
  });
}

void PortPage::AddPort(ComPortSettings* settings) {
  // Create new port manager
  ComPortManager* port_mgr = new ComPortManager(settings);
  port_mgr_list_.append(port_mgr);

  // Connect views to this port manager
  foreach (PortView* view, view_list_) {
    connect(port_mgr, SIGNAL(Receive(DataPacket&)),
            view, SLOT(OnReceivedData(DataPacket&)));
  }

  // Create thread for this port manager
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  port_mgr->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  // TODO: refaire les connexions avec les vues et les widgets
  // et/ou appeler directement les méthodes dédiées des widgets ?

//  connect(port_info_, &PortInfoWidget::OpenPortClicked,
//          port_mgr, &ComPortManager::OpenPort);
//  connect(port_info_, &PortInfoWidget::ClosePortClicked,
//          port_mgr, &ComPortManager::ClosePort);

  //port_info_->SetPortSettings(port_mgr->GetPortSettings());
  port_info_area_widget_->AddPort(port_mgr_list_.size()-1);
  send_widget_->PortListUpdated(); // TODO : à modifier, moisi
  // TODO delete this, work with lists in port info widget
  // warn info widget and send widget that new port has been added
}

void PortPage::DeletePort(quint8 port_idx) {
  // Delete threads
  QThread* thread = thread_list_.at(port_idx);
  thread->quit();
  if (!thread->wait(1000)) {
    qDebug() << "Timeout arret du thread.";
  }
  delete thread;
  thread_list_.removeAt(port_idx);

  // Delete port managers
  ComPortManager* port_mgr = port_mgr_list_.at(port_idx);
  delete port_mgr;
  port_mgr_list_.removeAt(port_idx);

  port_info_area_widget_->DeletePort(port_idx);

  // TODO il faut remettre à jour les port index des widgets qui en dépendent (portinfo par exemple)
}

QList<PortView*>* PortPage::GetViewList(void) {
  return &view_list_;
}

QList<ComPortManager*>* PortPage::GetPortMgrList(void) {
  return &port_mgr_list_;
}

void PortPage::SetPageIndex(quint32 page_idx) {
  page_index_ = page_idx;
}

void PortPage::OnOpenPortClicked(void) {
  //  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  //  port_mgr->OpenPort();
}

void PortPage::OnClosePortClicked(void) {
  //  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  //  port_mgr->ClosePort();
}
