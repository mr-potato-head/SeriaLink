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
#include "src/session.h"

PageSelector::PageSelector(QWidget *parent)
  : QWidget(parent) {
  button_layout_ = new QHBoxLayout(this);
  signal_mapper_ = new QSignalMapper(this);
}

void PageSelector::SetSession(Session* session) {
  session_ = session;

  connect(signal_mapper_, SIGNAL(mapped(int)),
          session, SLOT(SetCurrentPageIndex(int)));
}

void PageSelector::AddButton() {
  QPushButton* button = new QPushButton(this);
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button->setCheckable(true);
  button_list_.append(button);
  button_layout_->addWidget(button);
  QHBoxLayout* layout = new QHBoxLayout(button);

  QPushButton* deleteButton = new QPushButton(button);
  deleteButton->setIcon(QIcon(":/icons/icons/circle-x-8x.png"));
  layout->addStretch(90);
  layout->addWidget(deleteButton);
  connect(deleteButton, &QPushButton::clicked, [=](void) {
    int idx = button_list_.indexOf(button);
    session_->DeletePage(idx);
  });

  connect(button, SIGNAL(clicked()), signal_mapper_, SLOT(map()));
  signal_mapper_->setMapping(button, button_list_.size()-1);
}

void PageSelector::DeleteButton(quint8 page_idx) {
  QPushButton* button = button_list_.at(page_idx);
  button_list_.removeAt(page_idx);
  delete button;

  int index = 0;
  foreach (QPushButton* button, button_list_) {
    connect(button, SIGNAL(clicked()), signal_mapper_, SLOT(map()));
    signal_mapper_->setMapping(button, index);
    index++;
  }
}

void PageSelector::UpdateButtonName(quint8 page_idx) {
  // Get port name
  PortPage* page = session_->GetPortPageList()->at(page_idx);
  QList<ComPortManager*>* port_mgr_list = page->GetPortMgrList();

  QList<ComPortManager*>::iterator itBeginTh = port_mgr_list->begin();
  QList<ComPortManager*>::iterator itEndTh = port_mgr_list->end();
  QString page_name;
  for (QList<ComPortManager*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
    page_name += "-" + (*it)->GetPortSettings()->GetPortInfo().portName() + "-";
  }
  button_list_.at(page_idx)->setText(page_name);
}

void PageSelector::SetCheckedState(qint32 page_index) {
  foreach(QPushButton* button, button_list_) {
    button->setChecked(false);
  }
  button_list_.at(page_index)->setChecked(true);
}
