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

#include "src/topbar.h"

TopBar::TopBar(QWidget *parent) :
  QWidget(parent) {
  page_selector_ = new PageSelector(this);
  page_switcher_ = new PageSwitcher(this);
  main_layout_ = new QHBoxLayout(this);
  main_layout_->addWidget(page_selector_);
  main_layout_->addWidget(page_switcher_);

  main_layout_->setStretchFactor(static_cast<QWidget*>(page_selector_), 80);
  main_layout_->setStretchFactor(static_cast<QWidget*>(page_switcher_), 20);

  main_layout_->setMargin(0);
  main_layout_->setSpacing(0);

  connect(page_switcher_, SIGNAL(IncreaseCurrentPageIndex()),
          this, SLOT(OnIncreaseCurrentPageIndex()));
  connect(page_switcher_, SIGNAL(DecreaseCurrentPageIndex()),
          this, SLOT(OnDecreaseCurrentPageIndex()));
  connect(page_switcher_, SIGNAL(AddPage()),
          this, SIGNAL(AddPage()));
}

void TopBar::OnIncreaseCurrentPageIndex(void) {
  if (page_number_ > 0) {
    if (page_index_ < page_number_-1) {
      page_index_++;
      emit PageIndexUpdated(page_index_);
    }
  }
}

void TopBar::OnDecreaseCurrentPageIndex(void) {
  if (page_number_ > 0) {
    if (page_index_ > 0) {
      page_index_--;
      emit PageIndexUpdated(page_index_);
    }
  }
}
