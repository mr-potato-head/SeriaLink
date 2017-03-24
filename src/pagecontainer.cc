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

PageContainer::PageContainer(Session* session,
                             QWidget *parent)
  : QStackedWidget(parent),
    session_{session} {
  // Register metatypes
  qRegisterMetaType<ViewSettings>("ViewSettings");

  connect(session, SIGNAL(PortAdded(qint32)),
          this, SLOT(AddPage(qint32)));
  connect(session, SIGNAL(IndexChanged(qint32)),
          this, SLOT(setCurrentIndex(int)));
  connect(session, SIGNAL(ViewAdded(qint8, ViewSettings*)),
          this, SLOT(OnViewAdded(qint8, ViewSettings*)));
}

void PageContainer::AddPage(qint32 page_idx) {
  PortPage* page = new PortPage(session_, page_idx, this);
  page_list_.append(page);

  this->insertWidget(page_idx, page);
  this->setCurrentIndex(page_idx);
}

void PageContainer::OnViewAdded(qint8 page_idx, ViewSettings* view_settings) {
  page_list_.at(page_idx)->AddView(view_settings);
}
