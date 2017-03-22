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

#include "src/pagecontainer.h"

PageContainer::PageContainer(SessionManager* session_manager,
                             QWidget *parent)
  : QStackedWidget(parent),
    session_manager_{session_manager} {
  connect(session_manager_->GetCurrentSession(), SIGNAL(PortAdded(qint32)),
          this, SLOT(AddPage(qint32)));
  connect(session_manager_->GetCurrentSession(), SIGNAL(IndexChanged(qint32)),
          this, SLOT(setCurrentIndex(int)));
  connect(session_manager_, SIGNAL(AddView(qint8, QJsonObject)),
          this, SLOT(AddView(qint8, QJsonObject)));
}

void PageContainer::AddPage(qint32 port_index) {
  PortPage* page = new PortPage(session_manager_, port_index, this);
  page_list_.append(page);

  this->insertWidget(port_index, page);
  this->setCurrentIndex(port_index);
}

void PageContainer::AddView(qint8 page_idx, QJsonObject view_object) {
  page_list_.at(page_idx)->AddView(view_object);
}
