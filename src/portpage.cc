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
#include "src/terminalportview.h"
#include "src/dumpportview.h"
#include "src/tableportview.h"

PortPage::PortPage(SessionManager* session_manager,
                   qint32 port_index,
                   QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager},
    port_index_{port_index} {
  port_info_ = new PortInfoWidget(session_manager_, port_index, this);
  send_widget_ = new SendWidget(session_manager_, port_index, this);
  view_widget_ = new QWidget(this);
  view_layout_ = new QHBoxLayout(view_widget_);

  connect(port_info_, SIGNAL(NewViewClicked()),
          this, SLOT(OnNewViewClicked()));

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
    AddView(view_settings);
    break;
  }
  case QDialog::Rejected:
  default:
    break;
  }
}

void PortPage::AddView(ViewSettings* view_settings) {
  PortView* view;
  switch (view_settings->GetViewType()) {
  case ViewSettings::ViewType::kDump:
    view = new DumpPortView(view_settings, this);
    break;
  case ViewSettings::ViewType::kTerminal:
    view = new TerminalPortView(view_settings, this);
    break;
  case ViewSettings::ViewType::kTable:
    view = new TablePortView(view_settings, this);
    break;
  default:
    break;
  }
  view_layout_->addWidget(view);

  Session* session = session_manager_->GetCurrentSession();
  ComPortManager* port_mgr = session->GetPortManager(port_index_);

  // Connect received data to port
  connect(port_mgr, SIGNAL(Receive(const DataPacket&)),
          view, SLOT(OnReceivedData(const DataPacket&)));
}
