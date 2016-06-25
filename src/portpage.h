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
#include "src/sessionmanager.h"
#include "src/portinfowidget.h"
#include "src/portview.h"
#include "src/sendwidget.h"
#include "src/viewsettingdialog.h"
#include "src/viewsettings.h"

class PortPage : public QWidget {
  Q_OBJECT

 public:
  explicit PortPage(SessionManager* session_manager,
                    qint32 port_index,
                    QWidget *parent = 0);

 private slots: //NOLINT
  //! Executed when new view button is clicked
  void OnNewViewClicked(void);

 private:
  //! Main grid layout of the page
  QGridLayout* main_layout_ {NULL};

  //! Pointer on session manager
  SessionManager* session_manager_ {NULL};

  //! Port index in session
  qint32 port_index_ {-1};

  //! Port info widget of the page
  PortInfoWidget* port_info_ {NULL};

  //! Send widget of the page
  SendWidget* send_widget_ {NULL};

  //! Generic widget for views
  QWidget* view_widget_ {NULL};

  //! QHBoxLayout for views
  QHBoxLayout* view_layout_ {NULL};
};

#endif  // SRC_PORTPAGE_H_
