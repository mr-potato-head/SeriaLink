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

#ifndef SRC_SESSION_H_
#define SRC_SESSION_H_

#include <QObject>
#include <QList>
#include <QThread>
#include "src/localcomport.h"
#include "src/comportsettings.h"

class Session : public QObject {
  Q_OBJECT

 public:
  //! Default constructor
  explicit Session(QObject *parent = 0);

  //! Destructor
  ~Session();

  //! Add port in this session
  void AddPort(ComPortSettings* port_settings);

  //! Get port by index
  ComPort* GetPort(qint32 index);

  //! Get current port
  ComPort* GetCurrentPort(void);

  //! Get page number
  quint8 GetPageNumber(void);

  //! Get current page index
  quint8 GetCurrentPortIndex(void);

 public slots: //NOLINT
  //! Set current port index
  void SetCurrentPortIndex(qint32 index);

  //! Open port
  void OpenPort(qint32 index);

  //! Close port
  void ClosePort(qint32 index);

 signals:
  //! Emitted when a new port is added in session
  void PortAdded(qint32);

  //! Emitted when the current port index is changed
  void IndexChanged(qint32);

  //! Emitted for opening the port
  void OpenPortSignal(void);

  //! Emitted for closing the port
  void ClosePortSignal(void);

 private:
  //! COM port list
  QList<ComPort*> com_port_list_;

  //! Thread list
  QList<QThread*> thread_list_;

  //! Index of the current port;
  qint8 current_port_index_ {-1};
};

#endif  // SRC_SESSION_H_
