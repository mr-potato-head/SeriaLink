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

#include <QPushButton>
#include "src/pageselector.h"

PageSelector::PageSelector(SessionManager* session_manager,
                           QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager} {
  button_layout_ = new QHBoxLayout(this);
  signal_mapper_ = new QSignalMapper(this);

  connect(signal_mapper_,
          SIGNAL(mapped(int)),
          session_manager_->GetCurrentSession(),
          SLOT(SetCurrentPortMgrIndex(qint32)));
}

void PageSelector::AddButton(qint32 port_index) {
  // Get port name
  ComPortManager* port_manager = session_manager_->GetCurrentSession()->GetPortManager(port_index);
  ComPortSettings* portSettings = port_manager->GetPortSettings();

  QPushButton* button = new QPushButton(portSettings->GetPortInfo().portName());
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button->setCheckable(true);
  button_list_.append(button);
  button_layout_->addWidget(button);

  connect(button, SIGNAL(clicked()), signal_mapper_, SLOT(map()));
  signal_mapper_->setMapping(button, port_index);
}

void PageSelector::SetCheckedState(qint32 port_index) {
  foreach(QPushButton* button, button_list_) {
    button->setChecked(false);
  }
  button_list_.at(port_index)->setChecked(true);
}
