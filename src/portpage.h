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

#ifndef SRC_PORTPAGE_H_
#define SRC_PORTPAGE_H_

#include <QWidget>
#include <QGridLayout>
#include <QMap>
#include <QList>
#include "src/portinfowidget.h"
#include "src/portview.h"
#include "src/sendwidget.h"
#include "src/viewsettingdialog.h"
#include "src/viewsettings.h"
#include "src/comportmanager.h"
#include "src/portinfoareawidget.h"

class Session;

class PortPage : public QWidget {
  Q_OBJECT

 public:
  explicit PortPage(Session* session,
                    int page_index,
                    QWidget* parent = 0);

  //! Destructor
  ~PortPage(void);

  //! Add view in page
  void AddView(ViewSettings* settings);

  //! Add port in page
  void AddPort(ComPortSettings* settings);

  //! Delete port in page
  void DeletePort(int port_idx);

  //! Get view list
  QList<PortView*>* GetViewList(void);

  //! Get port manager list
  QList<ComPortManager*>* GetPortMgrList(void);

  //! Set page index
  void SetPageIndex(int page_idx);

 private slots: //NOLINT
  //! Executed when new view button is clicked
  void OnNewViewClicked(void);

  //! Executed when new port button is clicked
  void OnNewPortClicked(void);

  //! Executed on click on open button
  void OnOpenPortClicked(void);

  //! Executed on click on close button
  void OnClosePortClicked(void);

 private:
  //! Main grid layout of the page
  QGridLayout* main_layout_ {NULL};

  //! Pointer on session
  Session* session_ {NULL};

  //! Page index in session
  int page_index_ {0};

  //! Port info widget of the page
  //PortInfoWidget* port_info_ {NULL};

  //! Port info widget area
  PortInfoAreaWidget* port_info_area_widget_ {NULL};

  //! Send widget of the page
  SendWidget* send_widget_ {NULL};

  //! Generic widget for views
  QWidget* view_widget_ {NULL};

  //! QHBoxLayout for views
  QHBoxLayout* view_layout_ {NULL};

  //! Vertical left layout
  QVBoxLayout* left_vlayout_ {NULL};

  //! Left top grid layout
  QGridLayout* left_glayout_ {NULL};

  //! Add port button
  QPushButton* add_port_button_ {NULL};

  //! Add view button
  QPushButton* add_view_button_ {NULL};

  //! View list
  QList<PortView*> view_list_;

  //! Comport manager list
  QList<ComPortManager*> port_mgr_list_;

  //! Thread list
  QList<QThread*> thread_list_;
};

#endif  // SRC_PORTPAGE_H_
