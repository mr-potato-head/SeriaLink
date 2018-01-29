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

#ifndef SRC_PORTINFOAREAWIDGET_H_
#define SRC_PORTINFOAREAWIDGET_H_

#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include "src/comportmanager.h"
#include "src/portinfowidget.h"

class Session;

class PortInfoAreaWidget : public QScrollArea {
  Q_OBJECT
 public:
  explicit PortInfoAreaWidget(Session* session, int page_idx,
                              QWidget *parent = 0);

  void AddPort(int port_idx);

  void DeletePort(int port_idx);

 private:
  QVBoxLayout* main_layout_ {nullptr};

  Session* session_ {nullptr};

  QList<PortInfoWidget*> port_info_widget_list_;

  int page_idx_ {0};
};

#endif  // SRC_PORTINFOAREAWIDGET_H_
