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

PortInfoWidget::PortInfoWidget(Session* session,
                               qint32 port_index,
                               QWidget *parent)
  : QWidget(parent),
    session_{session},
    port_index_{port_index}
{
  // Get port settings
  ComPortManager* port = session->GetPortManager(port_index);
  ComPortSettings* port_settings = port->GetPortSettings();
  port_settings_ = port_settings;

  // Port name
  port_name_label_ = new QLabel(tr("Port name:"), this);
  port_name_value_  = new QLabel(
                        port_settings->GetPortInfo().portName(), this);
  port_name_value_->setAlignment(Qt::AlignHCenter);

  // Port baud rate
  port_baud_rate_label_ = new QLabel(tr("Port baud rate:"), this);
  qint32 baud_rate = static_cast<qint32>(port_settings->GetBaudRate());
  port_baud_rate_value_ = new QLabel(QString::number(baud_rate), this);
  port_baud_rate_value_->setAlignment(Qt::AlignHCenter);

  // Port parity
  QString parity_str;
  switch (port_settings->GetParity()) {
    case QSerialPort::NoParity:
      parity_str = tr("None");
    break;
    case QSerialPort::EvenParity:
      parity_str = tr("Even");
    break;
    case QSerialPort::OddParity:
      parity_str = tr("Odd");
    break;
    case QSerialPort::MarkParity:
      parity_str = tr("Mark");
    break;
    case QSerialPort::SpaceParity:
      parity_str = tr("Space");
    break;
    case QSerialPort::UnknownParity:
      parity_str = tr("Unknown");
    break;
  }

  port_parity_label_  = new QLabel(tr("Port parity:"), this);
  port_parity_value_  = new QLabel(parity_str, this);
  port_parity_value_->setAlignment(Qt::AlignHCenter);

  // Port data bits
  port_data_bits_label_  = new QLabel(tr("Port data bits:"), this);
  qint32 data_bits = static_cast<qint32>(port_settings->GetDataBits());
  port_data_bits_value_ = new QLabel(QString::number(data_bits), this);
  port_data_bits_value_->setAlignment(Qt::AlignHCenter);

  // Stop bits
  QString stop_bits_str;
  switch (port_settings->GetStopBits()) {
    case QSerialPort::OneStop:
      stop_bits_str = tr("1");
    break;
    case QSerialPort::OneAndHalfStop:
      stop_bits_str = tr("1.5");
    break;
    case QSerialPort::TwoStop:
      stop_bits_str = tr("2");
    break;
    case QSerialPort::UnknownStopBits:
      stop_bits_str = tr("Unknown");
    break;
  }

  port_stop_bits_label_  = new QLabel(tr("Port stop bits:"), this);
  port_stop_bits_value_  = new QLabel(stop_bits_str, this);
  port_stop_bits_value_->setAlignment(Qt::AlignHCenter);

  // Flow control
  QString flow_control_str;
  switch (port_settings->GetFlowControl()) {
    case QSerialPort::NoFlowControl:
      flow_control_str = tr("None");
    break;
    case QSerialPort::HardwareControl:
      flow_control_str = tr("RTS/CTS");
    break;
    case QSerialPort::SoftwareControl:
      flow_control_str = tr("XON/XOFF");
    break;
    case QSerialPort::UnknownFlowControl:
      flow_control_str = tr("Unknown");
    break;
  }

  port_flow_control_label_  = new QLabel(tr("Port flow control:"), this);
  port_flow_control_value_  = new QLabel(flow_control_str, this);
  port_flow_control_value_->setAlignment(Qt::AlignHCenter);

  // Create buttons
  open_button_ = new QPushButton(this);
  open_button_->setIcon(QIcon(":/icons/icons/media-play-8x.png"));
  open_button_->setToolTip(tr("Open serial port."));
  connect(open_button_, SIGNAL(clicked()),
          this, SLOT(OnOpenPortClicked()));
  close_button_ = new QPushButton(this);
  close_button_->setIcon(QIcon(":/icons/icons/media-stop-8x.png"));
  close_button_->setToolTip(tr("Close serial port."));
  connect(close_button_, SIGNAL(clicked()),
          this, SLOT(OnClosePortClicked()));
  new_view_button_ = new QPushButton(this);
  new_view_button_->setIcon(QIcon(":/icons/icons/plus-8x.png"));
  new_view_button_->setToolTip(tr("Add a view for this port."));
  connect(new_view_button_, SIGNAL(clicked()),
          this, SIGNAL(NewViewClicked()));

  settings_group_box_ = new QGroupBox(tr("Port settings"), this);
  group_box_layout_ = new QVBoxLayout(settings_group_box_);
  group_box_layout_->addWidget(port_name_label_);
  group_box_layout_->addWidget(port_name_value_);
  group_box_layout_->addWidget(port_baud_rate_label_);
  group_box_layout_->addWidget(port_baud_rate_value_);
  group_box_layout_->addWidget(port_parity_label_);
  group_box_layout_->addWidget(port_parity_value_);
  group_box_layout_->addWidget(port_data_bits_label_);
  group_box_layout_->addWidget(port_data_bits_value_);
  group_box_layout_->addWidget(port_stop_bits_label_);
  group_box_layout_->addWidget(port_stop_bits_value_);
  group_box_layout_->addWidget(port_flow_control_label_);
  group_box_layout_->addWidget(port_flow_control_value_);

  main_layout_ = new QVBoxLayout(this);
  main_layout_->addWidget(settings_group_box_);
  main_layout_->addWidget(open_button_);
  main_layout_->addWidget(close_button_);
  main_layout_->addWidget(new_view_button_);

  settings_group_box_->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);

  this->setSizePolicy(QSizePolicy::Expanding,
                      QSizePolicy::Expanding);
}

void PortInfoWidget::OnOpenPortClicked(void) {
  session_->OpenPort(port_index_);
}

void PortInfoWidget::OnClosePortClicked(void) {
  session_->ClosePort(port_index_);
}
