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

#ifndef SRC_SENDWIDGET_H_
#define SRC_SENDWIDGET_H_

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QGroupBox>
#include <QRadioButton>
#include "src/sessionmanager.h"
#include "src/manualmodepage.h"
#include "src/dumpmodepage.h"

class SendWidget : public QWidget {
  Q_OBJECT

 public:
  //! Enum of modes
  enum class MODES {
    MANUAL,
    DUMP,
    AUTO
  };

  //! Default constructor
  explicit SendWidget(SessionManager* session_manager,
                      qint32 port_index, QWidget *parent = 0);

 private:
  //! Main grid layout of the widget
  QGridLayout* main_layout_ {NULL};

  //! Session manager
  SessionManager* session_manager_ {NULL};

  //! Port index
  qint32 port_index_ {-1};

  //! Mode label
  QLabel* mode_label_ {nullptr};

  //! Mode combo box
  QComboBox* mode_combobox_ {nullptr};

  //! Mode stacked widget
  QStackedWidget* stacked_widget_ {nullptr};

  //! QWidget of the manual mode page
  ManualModePage* manual_mode_page_ {nullptr};

  //! QWidget of the dump mode page
  DumpModePage* dump_mode_page_ {nullptr};

  //! Vertical layout of the mode choice system
  QVBoxLayout* mode_layout_ {nullptr};
};

#endif  // SRC_SENDWIDGET_H_
