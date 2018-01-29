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

#include "src/portinfoareawidget.h"

PortInfoAreaWidget::PortInfoAreaWidget(Session* session, int page_idx,
                                       QWidget *parent)
  : QScrollArea(parent), session_(session), page_idx_ {page_idx} {
  QWidget *widget = new QWidget();
  this->setWidget(widget);
  this->setWidgetResizable(true);

  main_layout_ = new QVBoxLayout();
  widget->setLayout(main_layout_);
}

void PortInfoAreaWidget::AddPort(int port_idx) {
  PortInfoWidget* port_info = new PortInfoWidget(session_, page_idx_,
                                                 port_idx, this);
  port_info_widget_list_.append(port_info);
  main_layout_->addWidget(port_info);

  // Prevent from last widget deletion
  if (port_info_widget_list_.size() == 1) {
    port_info_widget_list_.at(0)->SetLastInList(true);
  } else {
    foreach (PortInfoWidget* port_info, port_info_widget_list_) { // NOLINT
      port_info->SetLastInList(false);
    }
  }
}

void PortInfoAreaWidget::DeletePort(int port_idx) {
  PortInfoWidget* port_info = port_info_widget_list_.at(port_idx);
  port_info_widget_list_.removeAt(port_idx);
  main_layout_->removeWidget(port_info);
  delete port_info;

  int index = 0;
  foreach (PortInfoWidget* port_info, port_info_widget_list_) { // NOLINT
    port_info->SetPortIndex(index);
    index++;
  }

  // Prevent from last widget deletion
  if (port_info_widget_list_.size() == 1) {
    port_info_widget_list_.at(0)->SetLastInList(true);
  }
}
