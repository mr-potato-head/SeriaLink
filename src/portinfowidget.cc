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

#include "src/portinfowidget.h"
#include "src/addormodifyportdialog.h"
#include "src/session.h"

PortInfoWidget::PortInfoWidget(Session* session,
                               int page_idx,
                               int port_idx,
                               QWidget *parent)
  : QGroupBox(parent),
    page_idx_ {page_idx},
    port_idx_ {port_idx},
    session_ {session} {
  QList<PortPage*>* page_list_ = session->GetPortPageList();
  port_mgr_ = page_list_->at(page_idx)->GetPortMgrList()->at(port_idx);

  this->setTitle(tr("Port"));
  main_layout_ = new QGridLayout(this);


  ComPortSettings* settings = port_mgr_->GetPortSettings();

  // Port name
  QString name = settings->GetPortInfo().portName();
  port_name_ = new QLabel(name, this);
  port_name_->setAlignment(Qt::AlignHCenter);
  main_layout_->addWidget(port_name_, 0, 0);

  // Port baud rate
  QString baudrate = QString::number(settings->GetBaudRate());
  port_baud_rate_ = new QLabel(baudrate, this);
  port_baud_rate_->setAlignment(Qt::AlignHCenter);
  main_layout_->addWidget(port_baud_rate_, 0, 1);

  // Create buttons
  open_button_ = new QPushButton(this);
  open_button_->setIcon(QIcon(":/icons/icons/media-play-8x.png"));
  open_button_->setToolTip(tr("Open serial port."));
  open_button_->setEnabled(true);
  connect(open_button_, SIGNAL(clicked()),
          port_mgr_, SLOT(OpenPort()));
  connect(open_button_, &QPushButton::clicked, [=](void) {
    open_button_->setEnabled(false);
    modify_button_->setEnabled(false);
    close_button_->setEnabled(true);
  });
  main_layout_->addWidget(open_button_, 1, 0);

  close_button_ = new QPushButton(this);
  close_button_->setIcon(QIcon(":/icons/icons/media-stop-8x.png"));
  close_button_->setToolTip(tr("Close serial port."));
  close_button_->setEnabled(false);
  connect(close_button_, SIGNAL(clicked()),
          port_mgr_, SLOT(ClosePort()));
  connect(close_button_, &QPushButton::clicked, [=](void) {
    open_button_->setEnabled(true);
    close_button_->setEnabled(false);
    modify_button_->setEnabled(true);
  });
  main_layout_->addWidget(close_button_, 1, 1);

  modify_button_ = new QPushButton(this);
  modify_button_->setIcon(QIcon(":/icons/icons/pencil-8x.png"));
  modify_button_->setToolTip(tr("Modify serial port."));
  modify_button_->setEnabled(true);
  connect(modify_button_, &QPushButton::clicked, [=](void) {
    AddOrModifyPortDialog updDialog(port_mgr_->GetPortSettings(),
                                    AddOrModifyPortDialog::ActionType::kUpdate,
                                    this);

    qint32 result = updDialog.exec();

    switch (result) {
    case QDialog::Accepted:
    {
      // Update labels
      QString name = settings->GetPortInfo().portName();
      port_name_->setText(name);

      // Port baud rate
      QString baudrate = QString::number(settings->GetBaudRate());
      port_baud_rate_->setText(baudrate);

      break;
    }
    case QDialog::Rejected:
    default:
      break;
    }
  });
  main_layout_->addWidget(modify_button_, 0, 2);

  delete_button_ = new QPushButton(this);
  delete_button_->setIcon(QIcon(":/icons/icons/trash-8x.png"));
  delete_button_->setToolTip(tr("Delete serial port."));
  delete_button_->setEnabled(true);
  connect(delete_button_, &QPushButton::clicked, [=](void) {
    session_->DeletePort(page_idx, port_idx);
  });
  main_layout_->addWidget(delete_button_, 1, 2);
}

void PortInfoWidget::SetPortIndex(int port_index) {
  port_idx_ = port_index;
}

void PortInfoWidget::SetLastInList(bool last_in_list) {
  last_in_list_ = last_in_list;
  if (last_in_list) {
    delete_button_->setEnabled(false);
    delete_button_->setToolTip(tr("Each page must have at least one port."));
  } else {
    delete_button_->setEnabled(true);
    delete_button_->setToolTip(tr("Delete serial port."));
  }
}
