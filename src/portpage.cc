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

PortPage::PortPage(Session* session,
                   qint32 port_index,
                   QWidget* parent)
  : QWidget(parent),
    session_(session),
    port_index_{port_index} {
  port_info_ = new PortInfoWidget(this);
  send_widget_ = new SendWidget(this);
  view_widget_ = new QWidget(this);
  view_layout_ = new QHBoxLayout(view_widget_);

  connect(port_info_, SIGNAL(NewViewClicked()),
          this, SLOT(OnNewViewClicked()));
  connect(port_info_, SIGNAL(OpenPortClicked()),
          this, SLOT(OnOpenPortClicked()));
  connect(port_info_, SIGNAL(ClosePortClicked()),
          this, SLOT(OnClosePortClicked()));

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(port_info_, 0, 0);
  main_layout_->addWidget(view_widget_, 0, 1);
  main_layout_->addWidget(send_widget_, 1, 0, 1, 2);

  main_layout_->setColumnStretch(0, 20);
  main_layout_->setColumnStretch(1, 80);
  main_layout_->setRowStretch(0, 80);
}

void PortPage::OnNewViewClicked(void) {
  ViewSettings* view_settings = new ViewSettings();
  ViewSettingDialog view_setting_dialog(view_settings, this);
  qint32 result = view_setting_dialog.exec();

  switch (result) {
  case QDialog::Accepted:
  {
    session_->AddView(port_index_, view_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::AddView(PortView* view) {
  view_layout_->addWidget(view);
  view_list_.append(view);

  connect(view, &PortView::DeleteView, [=](PortView* view) {
    for (int i=0 ; i < view_list_.size() ; i++) {
      if (view_list_.at(i) == view) {
        delete view;
        view_list_.removeAt(i);
      }
    }
  });

  /*
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

  ComPortManager* port_mgr = session_->GetPortManager(port_index_);

  // Connect received data to port
  connect(port_mgr, SIGNAL(Receive(DataPacket&)),
          view, SLOT(OnReceivedData(DataPacket&)));
  connect(view, &PortView::DeleteView, [=](PortView* view) {
    for (int i=0 ; i<view_list_.size() ; i++) {
      if (view_list_.at(i) == view) {
        delete view;
        session_->DeleteView(port_index_, i);
      }
    }
  });
  */
}

void PortPage::AddPortMgr(ComPortManager* port_mgr) {
  port_mgr_list_.append(port_mgr);
  port_info_->SetPortSettings(port_mgr->GetPortSettings());
  send_widget_->SetPortManager(port_mgr);
}

QList<PortView*>* PortPage::GetViewList(void) {
  return &view_list_;
}

QList<ComPortManager*> PortPage::GetPortMgrList(void) {
  return port_mgr_list_;
}

void PortPage::OnOpenPortClicked(void) {
  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  port_mgr->OpenPort();
}

void PortPage::OnClosePortClicked(void) {
  ComPortManager* port_mgr = session_->GetPortManager(port_index_);
  port_mgr->ClosePort();
}
