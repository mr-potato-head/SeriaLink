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
                               quint8 page_idx,
                               quint8 port_idx,
                               QWidget *parent)
  : QGroupBox(parent),
    session_ {session},
    page_idx_ {page_idx},
    port_idx_ {port_idx} {

  port_mgr_ = session->GetPortPageList()->at(page_idx)->GetPortMgrList()->at(port_idx);

  this->setTitle(tr("Port"));
  main_layout_ = new QGridLayout(this);

  // Port name
  QString name = port_mgr_->GetPortSettings()->GetPortInfo().portName();
  port_name_ = new QLabel(name, this);
  port_name_->setAlignment(Qt::AlignHCenter);
  main_layout_->addWidget(port_name_, 0, 0);

  // Port baud rate
  QString baudrate = QString::number(port_mgr_->GetPortSettings()->GetBaudRate());
  port_baud_rate_ = new QLabel(baudrate, this);
  port_baud_rate_->setAlignment(Qt::AlignHCenter);
  main_layout_->addWidget(port_baud_rate_, 0, 1);


//  // Port parity
//  port_parity_label_  = new QLabel(tr("Port parity:"), this);
//  port_parity_value_  = new QLabel(this);
//  port_parity_value_->setAlignment(Qt::AlignHCenter);

//  // Port data bits
//  port_data_bits_label_  = new QLabel(tr("Port data bits:"), this);
//  port_data_bits_value_ = new QLabel(this);
//  port_data_bits_value_->setAlignment(Qt::AlignHCenter);

//  // Stop bits
//  port_stop_bits_label_  = new QLabel(tr("Port stop bits:"), this);
//  port_stop_bits_value_  = new QLabel(this);
//  port_stop_bits_value_->setAlignment(Qt::AlignHCenter);

//  // Flow control
//  port_flow_control_label_  = new QLabel(tr("Port flow control:"), this);
//  port_flow_control_value_  = new QLabel(this);
//  port_flow_control_value_->setAlignment(Qt::AlignHCenter);

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
    AddOrModifyPortDialog updateDialog(port_mgr_->GetPortSettings(),
                                       AddOrModifyPortDialog::ActionType::kUpdate,
                                       this);

    qint32 result = updateDialog.exec();

    switch (result) {
    case QDialog::Accepted:
    {
      // Update labels
      QString name = port_mgr_->GetPortSettings()->GetPortInfo().portName();
      port_name_->setText(name);

      // Port baud rate
      QString baudrate = QString::number(port_mgr_->GetPortSettings()->GetBaudRate());
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

  //this->setFixedHeight(200);

//  new_view_button_ = new QPushButton(this);
//  new_view_button_->setIcon(QIcon(":/icons/icons/plus-8x.png"));
//  new_view_button_->setToolTip(tr("Add a view to this port."));
//  connect(new_view_button_, SIGNAL(clicked()),
//          this, SIGNAL(NewViewClicked()));

//  new_port_button_ = new QPushButton(this);
//  new_port_button_->setIcon(QIcon(":/icons/icons/plus-8x.png"));
//  new_port_button_->setToolTip(tr("Add a port to this page."));
//  connect(new_port_button_, SIGNAL(clicked()),
//          this, SIGNAL(NewPortClicked()));

//  settings_group_box_ = new QGroupBox(tr("Port settings"), this);
//  group_box_layout_ = new QVBoxLayout(settings_group_box_);
//  group_box_layout_->addWidget(port_name_label_);
//  group_box_layout_->addWidget(port_name_value_);
//  group_box_layout_->addWidget(port_baud_rate_label_);
//  group_box_layout_->addWidget(port_baud_rate_value_);
//  group_box_layout_->addWidget(port_parity_label_);
//  group_box_layout_->addWidget(port_parity_value_);
//  group_box_layout_->addWidget(port_data_bits_label_);
//  group_box_layout_->addWidget(port_data_bits_value_);
//  group_box_layout_->addWidget(port_stop_bits_label_);
//  group_box_layout_->addWidget(port_stop_bits_value_);
//  group_box_layout_->addWidget(port_flow_control_label_);
//  group_box_layout_->addWidget(port_flow_control_value_);

//  main_layout_ = new QVBoxLayout(this);
//  main_layout_->addWidget(settings_group_box_);
//  main_layout_->addWidget(open_button_);
//  main_layout_->addWidget(close_button_);
//  main_layout_->addWidget(new_view_button_);
//  main_layout_->addWidget(new_port_button_);

//  settings_group_box_->setSizePolicy(QSizePolicy::Expanding,
//                                     QSizePolicy::Expanding);

//  this->setSizePolicy(QSizePolicy::Expanding,
//                      QSizePolicy::Expanding);
}

void PortInfoWidget::SetPortIndex(quint8 port_index) {
  port_idx_ = port_index;
}

//void PortInfoWidget::SetPortSettings(ComPortSettings* port_settings) {
//  port_name_value_->setText(port_settings->GetPortInfo().portName());
//  qint32 baud_rate = static_cast<qint32>(port_settings->GetBaudRate());
//  port_baud_rate_value_->setText(QString::number(baud_rate));
//  QString parity_str;
//  switch (port_settings->GetParity()) {
//    case QSerialPort::NoParity:
//      parity_str = tr("None");
//    break;
//    case QSerialPort::EvenParity:
//      parity_str = tr("Even");
//    break;
//    case QSerialPort::OddParity:
//      parity_str = tr("Odd");
//    break;
//    case QSerialPort::MarkParity:
//      parity_str = tr("Mark");
//    break;
//    case QSerialPort::SpaceParity:
//      parity_str = tr("Space");
//    break;
//    case QSerialPort::UnknownParity:
//      parity_str = tr("Unknown");
//    break;
//  }
//  port_parity_value_->setText(parity_str);
//  qint32 data_bits = static_cast<qint32>(port_settings->GetDataBits());
//  port_data_bits_value_->setText(QString::number(data_bits));

//  QString stop_bits_str;
//  switch (port_settings->GetStopBits()) {
//    case QSerialPort::OneStop:
//      stop_bits_str = tr("1");
//    break;
//    case QSerialPort::OneAndHalfStop:
//      stop_bits_str = tr("1.5");
//    break;
//    case QSerialPort::TwoStop:
//      stop_bits_str = tr("2");
//    break;
//    case QSerialPort::UnknownStopBits:
//      stop_bits_str = tr("Unknown");
//    break;
//  }
//  port_stop_bits_value_->setText(stop_bits_str);
//  QString flow_control_str;
//  switch (port_settings->GetFlowControl()) {
//    case QSerialPort::NoFlowControl:
//      flow_control_str = tr("None");
//    break;
//    case QSerialPort::HardwareControl:
//      flow_control_str = tr("RTS/CTS");
//    break;
//    case QSerialPort::SoftwareControl:
//      flow_control_str = tr("XON/XOFF");
//    break;
//    case QSerialPort::UnknownFlowControl:
//      flow_control_str = tr("Unknown");
//    break;
//  }
//  port_flow_control_value_->setText(flow_control_str);
//}
