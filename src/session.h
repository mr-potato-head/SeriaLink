/*
 * Copyright (C) 2020 Guilhem GUYONNET
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
  void DeletePage(int page_idx);

  //! Add port in page in this session
  void AddPort(int page_idx, ComPortSettings* port_settings);

  //! Add port in page from JSON array
  void AddPort(int page_idx, const QJsonObject& port_object);

  //! Delete port
  void DeletePort(int page_idx, int port_idx);

  //! Add view in page from view settings
  void AddView(int page_idx, ViewSettings* settings);

  //! Add view in page from JSON array
  void AddView(int page_idx, const QJsonObject& view_object);

  //! Get current page index
  int GetCurrentPageIndex(void);

  //! Get page list
  QList<PortPage*>* GetPortPageList(void);

  //! Close session
  void Close(void);

 public slots: //NOLINT
  //! Set current page index
  void SetCurrentPageIndex(int page_index);

  //! Load session from file
  void LoadFromFile(QString filepath);

  //! Save session in file
  void SaveInFile(QString filepath);

 signals:
  //! Emitted when the current port index is changed
  void IndexChanged(int);

  //! Emitted when the last page has been deleted
  void LastPageDeleted(void);

  //! Emitted when first page has been added
  void FirstPageAdded(void);

 private:
  //! Index of the current page index;
  int current_page_index_ {0};

  //! Pointer on page container
  PageContainer* page_container_ {NULL};

  //! Pointer on top bar
  TopBar* top_bar_ {NULL};

  //! Global list of pages
  QList<PortPage*> page_list_;
};

#endif  // SRC_SESSION_H_
