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

#ifndef SRC_LOCALCOMPORT_H_
#define SRC_LOCALCOMPORT_H_

#include <QSerialPort>
#include <QDebug>
#include <QTimer>
#include <QByteArray>
#include <src/comport.h>

class LocalComPort : public ComPort {
  Q_OBJECT

 public:
  //! Default constructor
  explicit LocalComPort(QObject *parent = 0);

 public slots: //NOLINT
  //! Executed to open port
  virtual void OpenPort(void);

  //! Executed to close port
  virtual void ClosePort(void);

  //! Executed to send data
  virtual void sendData(QByteArray data);

 private slots: //NOLINT
  //! Executed when data are ready to read on port
  void OnReadyRead(void);

  void OnTimeout(void);

 private:
  //! QSerialPort instance
  QSerialPort* serial_port_ {NULL};

  //! Simulation timer
  QTimer* simu_timer_ {NULL};
};

#endif  // SRC_LOCALCOMPORT_H_
