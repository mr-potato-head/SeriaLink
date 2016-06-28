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

#ifndef SRC_PORTVIEW_H_
#define SRC_PORTVIEW_H_

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include "src/viewsettings.h"

class PortView : public QWidget {
  Q_OBJECT

 public:
  explicit PortView(ViewSettings* view_settings,
                    QWidget *parent = 0);

 public slots: //NOLINT
  //! Executed when new data are received
  void OnReceivedData(QByteArray data);

 private:
  //! Main grid layout of the view
  QGridLayout* main_layout_ {NULL};

  //! Text edit of the view
  QTextEdit* text_edit_ {NULL};

  //! Settings of the view
  ViewSettings* view_settings_ {NULL};
};

#endif  // SRC_PORTVIEW_H_
