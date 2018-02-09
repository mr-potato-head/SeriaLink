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

#include "src/viewsettings.h"

const QMap<QString, ViewSettings::ViewType>
ViewSettings::kViewTypeFromString {
  {"dump", ViewSettings::ViewType::kDump},
  {"table", ViewSettings::ViewType::kTable},
  {"terminal", ViewSettings::ViewType::kTerminal}
};

const QMap<QString, ViewSettings::DisplayType>
ViewSettings::kDisplayTypeFromString {
  {"ascii", ViewSettings::DisplayType::kAscii},
  {"hex", ViewSettings::DisplayType::kHexa},
  {"dec", ViewSettings::DisplayType::kDec}
};

const QMap<QString, ViewSettings::DataSize>
ViewSettings::kDataSizeFromString {
  {"no_size", ViewSettings::DataSize::kNoSize},
  {"1_byte", ViewSettings::DataSize::k1Byte},
  {"2_bytes", ViewSettings::DataSize::k2Bytes},
  {"4_bytes", ViewSettings::DataSize::k4Bytes},
  {"8_bytes", ViewSettings::DataSize::k8Bytes},
};

const QMap<ViewSettings::ViewType, QString>
ViewSettings::kStringFromViewType {
  {ViewSettings::ViewType::kDump, "dump"},
  {ViewSettings::ViewType::kTable, "table"},
  {ViewSettings::ViewType::kTerminal, "terminal"}
};

const QMap<ViewSettings::DisplayType, QString>
ViewSettings::kStringFromDisplayType {
  {ViewSettings::DisplayType::kAscii, "ascii"},
  {ViewSettings::DisplayType::kHexa, "hex"},
  {ViewSettings::DisplayType::kDec, "dec"}
};

const QMap<ViewSettings::DataSize, QString>
ViewSettings::kStringFromDataSize {
  {ViewSettings::DataSize::kNoSize, "no_size"},
  {ViewSettings::DataSize::k1Byte, "1_byte"},
  {ViewSettings::DataSize::k2Bytes, "2_bytes"},
  {ViewSettings::DataSize::k4Bytes, "4_bytes"},
  {ViewSettings::DataSize::k8Bytes, "8_bytes"},
};

ViewSettings::ViewSettings() {}

ViewSettings::ViewSettings(QJsonObject view_object) {
  QString view_type_str = view_object["view_type"].toString();
  view_type_ = kViewTypeFromString.value(view_type_str);
  QString display_type_str = view_object["view_display"].toString();
  display_type_ = kDisplayTypeFromString.value(display_type_str);
  QString data_size_str = view_object["view_size"].toString();
  data_size_ = kDataSizeFromString.value(data_size_str);
}

ViewSettings::ViewType ViewSettings::GetViewType(void) {
  return view_type_;
}

ViewSettings::DisplayType ViewSettings::GetDisplayType(void) const {
  return display_type_;
}

ViewSettings::DataSize ViewSettings::GetDataSize(void) const {
  return data_size_;
}

int ViewSettings::GetDataBlockTimeout(void) const {
  return data_block_timeout_;
}

int ViewSettings::GetDataBlockSize(void) const {
  return data_block_size_;
}

void ViewSettings::SetViewType(ViewSettings::ViewType view_type) {
  view_type_ = view_type;
}

void ViewSettings::SetDisplayType(ViewSettings::DisplayType display_type) {
  display_type_ = display_type;
}

void ViewSettings::SetDataSize(DataSize data_size) {
  data_size_ = data_size;
}

void ViewSettings::SetDataBlockSize(int data_block_size) {
  data_block_size_ = data_block_size;
}

void ViewSettings::SetDataBlockTimeout(int data_block_timeout) {
  data_block_timeout_ = data_block_timeout;
}

QJsonObject ViewSettings::ToJson(void) {
  QJsonObject view_object;
  view_object["view_type"] = kStringFromViewType.value(view_type_);
  view_object["view_display"] = kStringFromDisplayType.value(display_type_);
  view_object["view_size"] = kStringFromDataSize.value(data_size_);
  return view_object;
}
