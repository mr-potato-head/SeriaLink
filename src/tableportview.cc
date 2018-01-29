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

#include <QHeaderView>
#include "src/tableportview.h"
#include "src/dataformatter.h"

TablePortView::TablePortView(ViewSettings* view_settings, QWidget* parent)
  : PortView{view_settings, parent} {
  table_widget_ = new QTableWidget(this);
  table_widget_->setColumnCount(2);
  table_widget_->setHorizontalHeaderLabels({tr("Datetime"), tr("Data")});
  QHeaderView *headerView = table_widget_->horizontalHeader();
  headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  headerView->setSectionResizeMode(1, QHeaderView::Interactive);
  headerView->setStretchLastSection(true);
  main_layout_->addWidget(table_widget_, 1, 0);

  // Signal connections
  connect(clear_button_, &QPushButton::clicked, [=](void) {
    table_widget_->clear();
    current_row_idx_ = 0;
  });
}

void TablePortView::OnReceivedData(DataPacket packet) {
  table_widget_->insertRow(current_row_idx_);

  QString dt = packet.GetDateTime().toString("dd/MM/yy - hh:mm:ss");
  QTableWidgetItem *dtItem = new QTableWidgetItem(dt);
  table_widget_->setItem(current_row_idx_, 0, dtItem);

  QString str = DataFormatter::formatData(*view_settings_, packet);
  QTableWidgetItem *strItem = new QTableWidgetItem(str);
  table_widget_->setItem(current_row_idx_, 1, strItem);

  if (capture_in_progress_) {
    *capture_stream_ << dt << ";" << str << "\r";
  }
  current_row_idx_++;
}

void TablePortView::OnDataSent(DataPacket packet) {
  table_widget_->insertRow(current_row_idx_);

  QString dt = packet.GetDateTime().toString("dd/MM/yy - hh:mm:ss");
  QTableWidgetItem *dtItem = new QTableWidgetItem(dt);
  table_widget_->setItem(current_row_idx_, 0, dtItem);

  QString str = DataFormatter::formatData(*view_settings_, packet);
  QTableWidgetItem *strItem = new QTableWidgetItem(str);
  table_widget_->setItem(current_row_idx_, 1, strItem);

  if (capture_in_progress_) {
    *capture_stream_ << dt << ";" << str << "\r";
  }
  current_row_idx_++;
}
