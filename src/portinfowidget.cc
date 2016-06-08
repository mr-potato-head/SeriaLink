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

PortInfoWidget::PortInfoWidget(SessionManager* session_manager,
                               qint32 port_index,
                               QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager},
    port_index_{port_index}
{
  // Get port settings
  Session* session = session_manager_->GetCurrentSession();
  ComPort* port = session->GetPort(port_index);
  ComPortSettings* port_settings = port->GetPortSettings();
  port_settings_ = port_settings;

  // Port name
  port_name_label_ = new QLabel(tr("Port name:"), this);
  port_name_value_  = new QLabel(
                        port_settings->GetPortInfo().portName(), this);

  // Port baud rate
  port_baud_rate_label_ = new QLabel(tr("Port baud rate:"), this);
  qint32 baud_rate = static_cast<qint32>(port_settings->GetBaudRate());
  port_baud_rate_value_ = new QLabel(QString::number(baud_rate), this);

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

  // Port data bits
  port_data_bits_label_  = new QLabel(tr("Port data bits:"), this);
  qint32 data_bits = static_cast<qint32>(port_settings->GetDataBits());
  port_data_bits_value_ = new QLabel(QString::number(data_bits), this);

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

  // Create buttons
  open_button_ = new QPushButton(tr("Open"), this);
  connect(open_button_, SIGNAL(clicked()),
          this, SLOT(OnOpenPortClicked()));
  close_button_ = new QPushButton(tr("Close"), this);
  connect(close_button_, SIGNAL(clicked()),
          this, SLOT(OnClosePortClicked()));

  main_layout_ = new QVBoxLayout(this);
  main_layout_->addWidget(port_name_label_);
  main_layout_->addWidget(port_name_value_);
  main_layout_->addWidget(port_baud_rate_label_);
  main_layout_->addWidget(port_baud_rate_value_);
  main_layout_->addWidget(port_parity_label_);
  main_layout_->addWidget(port_parity_value_);
  main_layout_->addWidget(port_data_bits_label_);
  main_layout_->addWidget(port_data_bits_value_);
  main_layout_->addWidget(port_stop_bits_label_);
  main_layout_->addWidget(port_stop_bits_value_);
  main_layout_->addWidget(port_flow_control_label_);
  main_layout_->addWidget(port_flow_control_value_);
  main_layout_->addWidget(open_button_);
  main_layout_->addWidget(close_button_);
}

void PortInfoWidget::OnOpenPortClicked(void) {
  Session* session = session_manager_->GetCurrentSession();
  session->OpenPort(port_index_);
}

void PortInfoWidget::OnClosePortClicked(void) {
  Session* session = session_manager_->GetCurrentSession();
  session->ClosePort(port_index_);
}
