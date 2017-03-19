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
#include <QJsonObject>
#include "src/comportmanager.h"
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

  //! Add port from JSON array
  void AddPort(const QJsonObject& port_object);

  //! Get port number
  quint8 GetPortNumber(void);

  //! Get current page index
  quint8 GetCurrentPortMgrIndex(void);

  //! Get a COM port manager
  ComPortManager* GetPortManager(qint32 index);

  void Close(void);

  //! Load ports for the session from JSON array
  void LoadPortsFromJson(const QJsonArray& session_pages);

 public slots: //NOLINT
  //! Set current port index
  void SetCurrentPortMgrIndex(qint32 index);

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
  QList<ComPortManager*> com_port_mgr_list_;

  //! Thread list
  QList<QThread*> thread_list_;

  //! Index of the current port manager;
  qint32 current_port_mgr_index_ {-1};
};

#endif  // SRC_SESSION_H_
