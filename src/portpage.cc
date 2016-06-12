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

PortPage::PortPage(SessionManager* session_manager,
                   qint32 port_index,
                   QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager},
    port_index_{port_index} {
  port_info_ = new PortInfoWidget(session_manager_, port_index, this);
  send_widget_ = new SendWidget(session_manager_, port_index, this);

  connect(port_info_, SIGNAL(NewViewClicked()),
          this, SLOT(OnNewViewClicked()));

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(port_info_, 0, 0);
  main_layout_->addWidget(send_widget_, 1, 0, 1, 2);
}

void PortPage::OnNewViewClicked(void) {
  static int index = 1;
  PortView* view = new PortView(this);
  main_layout_->addWidget(view, 0, index++);

  Session* session = session_manager_->GetCurrentSession();
  ComPort* port = session->GetPort(port_index_);

  // Connect received data to port
  connect(port, SIGNAL(receivedData(QByteArray)),
          view, SLOT(OnReceivedData(QByteArray)));

  // Connect to send data to port
  connect(send_widget_, SIGNAL(sendData(QByteArray)),
          port, SLOT(sendData(QByteArray)));
}
