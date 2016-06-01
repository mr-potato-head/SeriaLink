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


#include "src/pageswitcher.h"

PageSwitcher::PageSwitcher(QWidget *parent) :
  QWidget(parent) {
  right_button_ = new QPushButton(tr(">"), this);
  right_button_->setSizePolicy(QSizePolicy::Expanding,
                               QSizePolicy::Expanding);
  left_button_ = new QPushButton(tr("<"), this);
  left_button_->setSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Expanding);
  add_button_ = new QPushButton(tr("+"), this);
  add_button_->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);

  main_layout_ = new QHBoxLayout(this);
  main_layout_->addWidget(left_button_);
  main_layout_->addWidget(add_button_);
  main_layout_->addWidget(right_button_);
}

void PageSwitcher::EnableButton(ButtonType type) {
  switch (type) {
    case ButtonType::kDecreaseButton:
      left_button_->setEnabled(true);
    break;
    case ButtonType::kAddButton:
      add_button_->setEnabled(true);
    break;
    case ButtonType::kIncreaseButton:
      right_button_->setEnabled(true);
    break;
    default:
    break;
  }
}

void PageSwitcher::DisableButton(ButtonType type) {
  switch (type) {
    case ButtonType::kDecreaseButton:
      left_button_->setEnabled(false);
    break;
    case ButtonType::kAddButton:
      add_button_->setEnabled(false);
    break;
    case ButtonType::kIncreaseButton:
      right_button_->setEnabled(false);
    break;
    default:
    break;
  }
}
