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

#include "src/localcomport.h"

LocalComPort::LocalComPort(QObject *parent) :
  ComPort(parent) {
  port_type_ = PortType::kLocalPort;
}

void LocalComPort::OpenPort(void) {
  serial_port_ = new QSerialPort(com_port_settings_->GetPortInfo(), this);
  serial_port_->setBaudRate(com_port_settings_->GetBaudRate());
  serial_port_->setParity(com_port_settings_->GetParity());
  serial_port_->setDataBits(com_port_settings_->GetDataBits());
  serial_port_->setStopBits(com_port_settings_->GetStopBits());
  serial_port_->setFlowControl(com_port_settings_->GetFlowControl());

  connect(serial_port_, SIGNAL(error(QSerialPort::SerialPortError)),
          this, SIGNAL(PortErrorOccurred(QSerialPort::SerialPortError)));

  if (!serial_port_->open(QIODevice::ReadWrite)) {
    qDebug() << tr("Opening error.");
    qDebug() << serial_port_->errorString();
  } else {
    qDebug() << tr("Port ")
                + com_port_settings_->GetPortInfo().portName()
                + tr(" opened.");

    connect(serial_port_, SIGNAL(readyRead()),
            this, SLOT(OnReadyRead()));

    emit PortOpened();
  }
}

void LocalComPort::ClosePort(void) {
  serial_port_->close();
  qDebug() << tr("Port ")
              + com_port_settings_->GetPortInfo().portName()
              + tr(" closed.");
  emit PortClosed();
}

void LocalComPort::OnReadyRead(void) {
  DataPacket packet(serial_port_->readAll());
  emit DataReceived(packet);
}

void LocalComPort::Send(DataPacket packet) {
  QByteArray data = packet.GetData();
  serial_port_->write(data, data.size());
  emit DataSent(packet);
}

//! Getter of port status
bool LocalComPort::IsOpen(void) {
  return serial_port_->isOpen();
}
