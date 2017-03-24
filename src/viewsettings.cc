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

const QMap<QString, ViewSettings::ViewType> ViewSettings::kViewTypeMap
{
  {"dump", ViewSettings::ViewType::kDump},
  {"table", ViewSettings::ViewType::kTable},
  {"terminal", ViewSettings::ViewType::kTerminal}
};

const QMap<QString, ViewSettings::DisplayType> ViewSettings::kDisplayTypeMap
{
  {"ascii", ViewSettings::DisplayType::kAscii},
  {"hex", ViewSettings::DisplayType::kHexa},
  {"dec", ViewSettings::DisplayType::kDec}
};

const QMap<QString, ViewSettings::DataSize> ViewSettings::kDataSizeMap
{
  {"no_size", ViewSettings::DataSize::kNoSize},
  {"1_byte", ViewSettings::DataSize::k1Byte},
  {"2_bytes", ViewSettings::DataSize::k2Bytes},
  {"4_bytes", ViewSettings::DataSize::k4Bytes},
  {"8_bytes", ViewSettings::DataSize::k8Bytes},
};

ViewSettings::ViewSettings() {}

ViewSettings::ViewSettings(QJsonObject view_object) {
  view_type_ = kViewTypeMap.value(view_object["view_type"].toString());
  display_type_ = kDisplayTypeMap.value(view_object["view_display"].toString());
  data_size_ = kDataSizeMap.value(view_object["view_size"].toString());
}

ViewSettings::ViewType ViewSettings::GetViewType(void) {
  return view_type_;
}

ViewSettings::DisplayType ViewSettings::GetDisplayType(void) {
  return display_type_;
}

ViewSettings::DataSize ViewSettings::GetDataSize(void) {
  return data_size_;
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
