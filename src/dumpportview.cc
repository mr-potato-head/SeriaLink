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

#include "src/dumpportview.h"
#include "src/dataformatter.h"

DumpPortView::DumpPortView(ViewSettings* view_settings, QWidget* parent)
  : PortView{view_settings, parent} {
  text_edit_ = new QPlainTextEdit(this);
  main_layout_->addWidget(text_edit_, 1, 0);

  // Signal connections
  connect(clear_button_, &QPushButton::clicked, [=](void) {
    text_edit_->clear();
  });
}

void DumpPortView::OnReceivedData(const DataPacket& packet) {
  QString str = packet.GetDateTime().toString("dd.MM.yyyy at hh:mm:ss.zzz");
  str += "\r  ";
  str += DataFormatter::formatData(*view_settings_, packet);
  text_edit_->appendPlainText(str);
  if (capture_in_progress_) {
    *capture_stream_ << str;
  }
}

void DumpPortView::OnSentData(const DataPacket& packet) {
  QString str = packet.GetDateTime().toString("dd.MM.yyyy at hh:mm:ss.zzz");
  str += "\r  ";
  str += DataFormatter::formatData(*view_settings_, packet);
  text_edit_->appendPlainText(str);
  if (capture_in_progress_) {
    *capture_stream_ << str;
  }
}
