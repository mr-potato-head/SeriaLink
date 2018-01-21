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
#include "src/portpage.h"
#include "src/pagecontainer.h"
#include "src/topbar.h"

class Session : public QObject {
  Q_OBJECT

 public:
  //! Default constructor
  explicit Session(QObject *parent = 0);

  //! Destructor
  ~Session();

  //! Set TopBar pointer
  void SetTopbar(TopBar* top_bar);

  //! Set page container pointer
  void SetPageContainer(PageContainer* page_container);

  //! Add port in page in this session
  void AddPage(void);

  //! Add port in page in this session
  void AddPage(ComPortSettings* port_settings);

  //! Delete page in this session
  void DeletePage(quint8 page_idx);

  //! Add port in page in this session
  void AddPort(quint8 page_idx, ComPortSettings* port_settings);

  //! Add port in page from JSON array
  void AddPort(quint8 page_idx, const QJsonObject& port_object);

  //! Update port settings
  void UpdatePortSettings(quint8 page_idx,
                          quint8 port_idx,
                          ComPortSettings* port_settings);

  //! Delete port
  void DeletePort(quint8 page_idx, quint8 port_idx);

  //! Add view in page from view settings
  void AddView(quint8 page_idx, ViewSettings* settings);

  //! Add view in page from JSON array
  void AddView(quint8 page_idx, const QJsonObject& view_object);

  //! Update view in page
  void UpdateViewSettings(quint8 page_idx,
                          quint8 view_idx,
                          ViewSettings* settings);

  //! Delete view in page
  void DeleteView(quint8 page_idx, quint8 view_idx);

  //! Get port number
  //quint8 GetPortNumber(void);

  //! Get current page index
  quint8 GetCurrentPageIndex(void);

  //! Get a COM port manager
  //ComPortManager* GetPortManager(qint32 index);

  //! Get page list
  QList<PortPage*>* GetPortPageList(void);

  //! Close session
  void Close(void);

 public slots: //NOLINT
  //! Set current page index
  void SetCurrentPageIndex(int page_index);

  //! Open port
  //void OpenPort(qint32 index);

  //! Close port
  //void ClosePort(qint32 index);

  //! Load session from file
  void LoadFromFile(QString filepath);

  //! Save session in file
  void SaveInFile(QString filepath);

 signals:
  //! Emitted when a new port is added in session
  void PageAdded(quint32);

  //! Emitted when the current port index is changed
  void IndexChanged(quint32);

  //! Emitted for opening the port
  //void OpenPortSignal(void);

  //! Emitted for closing the port
  //void ClosePortSignal(void);

  //! Emitted for adding view
  //void ViewAdded(qint8, ViewSettings*);

 private:
  //! COM port list
  //QList<ComPortManager*> com_port_mgr_list_;

  //! Thread list
  //QList<QThread*> thread_list_;

  //! Index of the current page index;
  quint32 current_page_index_ {0};

  //! Pointer on page container
  PageContainer* page_container_ {NULL};

  //! Pointer on top bar
  TopBar* top_bar_ {NULL};

  //! Global list of pages
  QList<PortPage*> page_list_;
};

#endif  // SRC_SESSION_H_
