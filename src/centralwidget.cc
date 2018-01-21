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

#include <QDebug>
#include "src/centralwidget.h"
#include "src/menuwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
  QWidget(parent) {

  // Create widget
  page_container_ = new PageContainer(this);
  top_bar_ = new TopBar(this);

  // Instanciate session manager
  session_ = new Session(this);
  session_->SetTopbar(top_bar_);
  session_->SetPageContainer(page_container_);
  top_bar_->SetSession(session_);

  main_layout_ = new QVBoxLayout(this);
  main_layout_->addWidget(top_bar_);
  main_layout_->addWidget(page_container_);

  top_bar_->setFixedHeight(60);
//  main_layout_->setStretchFactor(static_cast<QWidget*>(top_bar_), 10);
//  main_layout_->setStretchFactor(static_cast<QWidget*>(page_container_), 90);

  main_layout_->setMargin(0);
  main_layout_->setSpacing(0);

  // Register metatypes
  qRegisterMetaType<DataPacket>("DataPacket");

  connect(top_bar_, &TopBar::OpenMenu, [=](void) {
    MenuWidget* menu = new MenuWidget(session_, this);
    QRect menu_geometry = menu->geometry();
    QRect top_bar_geometry = top_bar_->geometry();
    QPoint relative_bottom_right = top_bar_geometry.bottomRight();
    QPoint absolute_bottom_right = QWidget::mapToGlobal(relative_bottom_right);
    QPoint move_point(absolute_bottom_right.x()-menu_geometry.width(),
                      absolute_bottom_right.y());
    menu->move(move_point);
    menu->show();
    menu->setFocus();
  });
}

CentralWidget::~CentralWidget() {
  session_->Close();
  delete session_;
}

