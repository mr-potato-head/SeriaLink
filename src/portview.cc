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

#include "src/portview.h"

PortView::PortView(QWidget *parent)
  : QWidget(parent) {
  main_layout_ = new QGridLayout(this);
  text_edit_ = new QTextEdit(this);

  main_layout_->addWidget(text_edit_);
}

void PortView::OnReceivedData(QByteArray data) {
    text_edit_->append(QString(data));
}
