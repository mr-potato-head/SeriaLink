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
#include "src/viewsettings.h"

class Session : public QObject {
  Q_OBJECT

 public:

  class Page {
    public :
     QList<ComPortSettings*> port_setting_list_;
     QList<ViewSettings*> view_setting_list_;
  };

  //! Default constructor
  explicit Session(QObject *parent = 0);

  //! Destructor
  ~Session();

  //! Add port in page in this session
  void AddPort(ComPortSettings* port_settings);

  //! Add port in page in this session
  void AddPort(qint8 page_idx, ComPortSettings* port_settings);

  //! Add port in page from JSON array
  void AddPort(qint8 page_idx, const QJsonObject& port_object);

  //! Add view in page from view settings
  void AddView(qint8 page_idx, ViewSettings* view_settings);

  //! Add view in page from JSON array
  void AddView(qint8 page_idx, const QJsonObject& view_object);

  //! Delete view in page
  void DeleteView(qint8 page_idx, qint8 view_idx);

  //! Get port number
  quint8 GetPortNumber(void);

  //! Get current page index
  quint8 GetCurrentPortMgrIndex(void);

  //! Get a COM port manager
  ComPortManager* GetPortManager(qint32 index);

  //! Close session
  void Close(void);

 public slots: //NOLINT
  //! Set current port index
  void SetCurrentPortMgrIndex(qint32 index);

  //! Open port
  void OpenPort(qint32 index);

  //! Close port
  void ClosePort(qint32 index);

  //! Load session from file
  void LoadFromFile(QString filepath);

  //! Save session in file
  void SaveInFile(QString filepath);

 signals:
  //! Emitted when a new port is added in session
  void PortAdded(qint32);

  //! Emitted when the current port index is changed
  void IndexChanged(qint32);

  //! Emitted for opening the port
  void OpenPortSignal(void);

  //! Emitted for closing the port
  void ClosePortSignal(void);

  //! Emmitted for adding view
  void ViewAdded(qint8, ViewSettings*);

 private:
  //! COM port list
  QList<ComPortManager*> com_port_mgr_list_;

  //! Thread list
  QList<QThread*> thread_list_;

  //! Index of the current port manager;
  qint32 current_port_mgr_index_ {-1};

  //! Global list for load/save session
  QList<Page*> page_list_;
};

#endif  // SRC_SESSION_H_
