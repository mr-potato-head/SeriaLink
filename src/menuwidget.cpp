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

#include "src/menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent) {
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

  about_button_ = new QPushButton(this);
  about_button_->setIcon(QIcon(":/icons/icons/question-mark-8x.png"));
  about_button_->setFixedSize(60, 60);

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(about_button_);
}

void MenuWidget::focusOutEvent(QFocusEvent *) { //NOLINT
  close();
}
