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

#ifndef SRC_MENUWIDGET_H_
#define SRC_MENUWIDGET_H_

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "src/session.h"

class MenuWidget : public QWidget {
  Q_OBJECT

 public:
  //! Constructor
  explicit MenuWidget(Session* session,
                      QWidget *parent = 0);

 private:
  //! Maing grid layout
  QGridLayout* main_layout_ {nullptr};

  //! About button
  QPushButton* about_button_ {nullptr};

  //! Open session button
  QPushButton* open_session_button_ {nullptr};

  //! Session manager pointer
  Session* session_ {nullptr};
};

#endif  // SRC_MENUWIDGET_H_
