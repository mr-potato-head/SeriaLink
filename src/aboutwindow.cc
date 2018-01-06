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

#include "src/aboutwindow.h"
#include "src/version.h"

AboutWindow::AboutWindow(QWidget* parent)
  : QDialog(parent) {
  main_layout_ = new QGridLayout(this);
  version_label_ = new QLabel(VERSION, this);
  version_label_->setAlignment(Qt::AlignCenter);
  button_box_ = new QDialogButtonBox(QDialogButtonBox::Ok,
                                     Qt::Horizontal, this);
  connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
  main_layout_->addWidget(version_label_);
  main_layout_->addWidget(button_box_);
}
