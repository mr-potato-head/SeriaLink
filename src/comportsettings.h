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

#ifndef SRC_COMPORTSETTINGS_H_
#define SRC_COMPORTSETTINGS_H_

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonObject>

class ComPortSettings {
 public:
  //! Default constructor
  ComPortSettings();

  //! Getter of port infos
  QSerialPortInfo GetPortInfo(void);

  //! Getter of port baud rate
  QSerialPort::BaudRate GetBaudRate(void) const;

  //! Getter of port parity
  QSerialPort::Parity GetParity(void) const;

  //! Getter of data bits
  QSerialPort::DataBits GetDataBits(void) const;

  //! Getter of stop bits
  QSerialPort::StopBits GetStopBits(void) const;

  //! Getter of flow control
  QSerialPort::FlowControl GetFlowControl(void) const;

  //! Setter of port infos
  void SetPortInfo(QSerialPortInfo port_info);

  //! Setter of port baud rate
  void SetBaudRate(QSerialPort::BaudRate baud_rate);

  //! Setter of port parity
  void SetParity(QSerialPort::Parity parity);

  //! Setter of data bits
  void SetDataBits(QSerialPort::DataBits data_bits);

  //! Setter of stop bits
  void SetStopBits(QSerialPort::StopBits stop_bits);

  //! Setter of flow control
  void SetFlowControl(QSerialPort::FlowControl flow_control);

  //! Get JSON translation
  QJsonObject ToJson(void);

 private:
  //! Port infos
  QSerialPortInfo port_info_;

  //! Baud rate of the port
  QSerialPort::BaudRate port_baud_rate_ {QSerialPort::UnknownBaud};

  //! Parity of the port
  QSerialPort::Parity port_parity_ {QSerialPort::UnknownParity};

  //! Data bits of the port
  QSerialPort::DataBits port_data_bits_ {QSerialPort::UnknownDataBits};

  //! Stop bits of the port
  QSerialPort::StopBits port_stop_bits_ {QSerialPort::UnknownStopBits};

  //! Flow control of the port
  QSerialPort::FlowControl port_flow_control_ {QSerialPort::UnknownFlowControl};
};

#endif  // SRC_COMPORTSETTINGS_H_
