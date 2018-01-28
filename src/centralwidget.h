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

#ifndef SRC_CENTRALWIDGET_H_
#define SRC_CENTRALWIDGET_H_

#include <QWidget>
#include <QVBoxLayout>
#include "dragdroparea.h"
#include "src/topbar.h"
#include "src/pagecontainer.h"
#include "src/session.h"

class CentralWidget : public QWidget {
  Q_OBJECT
 public:
  //! Constructor
  explicit CentralWidget(QWidget *parent = 0);

  //! Destructor
  ~CentralWidget(void);

 private:
  //! Main layout of the window
  QVBoxLayout* main_layout_ {NULL};

  //! Top bar with menu
  TopBar* top_bar_ {NULL};

  //! Page container
  PageContainer* page_container_ {NULL};

  //! Session
  Session* session_ {NULL};

  //! Central darg & drop zone for session file
  DragDropArea* drag_drop_area_ {nullptr};
};

#endif  // SRC_CENTRALWIDGET_H_
