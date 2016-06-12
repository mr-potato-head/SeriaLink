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

#include "src/sendwidget.h"

SendWidget::SendWidget(SessionManager* session_manager,
                       qint32 port_index, QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager},
    port_index_{port_index} {
  send_button_ = new QPushButton(tr("Send >"), this);
  send_line_edit_ = new QLineEdit(this);

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(send_line_edit_, 0, 0);
  main_layout_->addWidget(send_button_, 0, 1);

  connect(send_button_, SIGNAL(clicked()),
          this, SLOT(OnSendButtonClicked()));
}

void SendWidget::OnSendButtonClicked(void) {
 emit sendData(send_line_edit_->text().toUtf8());
}
