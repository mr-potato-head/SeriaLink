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

#ifndef SRC_PORTINFOWIDGET_H_
#define SRC_PORTINFOWIDGET_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QList>
#include "src/comportmanager.h"
#include "src/comportsettings.h"

class Session;

class PortInfoWidget : public QGroupBox {
  Q_OBJECT

 public:
  //! Default constructor
  explicit PortInfoWidget(Session* session,
                          int page_idx,
                          int port_idx,
                          QWidget *parent = 0);

  void SetPortIndex(int port_index);
  void SetLastInList(bool last_in_list);

 private:
  //! Group box vertical layout
  QVBoxLayout* group_box_layout_ {NULL};

  //! Port name label
  QLabel* port_name_ {NULL};

  //! Port baud rate
  QLabel* port_baud_rate_ {NULL};

  //! Port parity parity/data bits/stop bits
  QLabel* port_settings_ {NULL};

  //! Port flow control label
  QLabel* port_flow_control_ {NULL};

  //! Port flow control value
  QLabel* port_flow_control_value_ {NULL};

  //! Open COM port button
  QPushButton* open_button_ {NULL};

  //! Close COM port button
  QPushButton* close_button_ {NULL};

  //! Modify COM port button
  QPushButton* modify_button_ {NULL};
  //! Delete COM port button
  QPushButton* delete_button_ {NULL};

//  //! Create new view
//  QPushButton* new_view_button_ {NULL};

//  //! Modify new port
//  QPushButton* new_port_button_ {NULL};

  //! COM Port manager list
  ComPortManager* port_mgr_ {NULL};

  QGridLayout* main_layout_ {NULL};

  int page_idx_ {0};
  int port_idx_ {0};
  Session* session_ {nullptr};
  bool last_in_list_ {false};
};

#endif  // SRC_PORTINFOWIDGET_H_
