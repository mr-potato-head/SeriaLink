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

ViewSettings::ViewSettings() {}

ViewSettings::ViewType ViewSettings::GetViewType(void) const {
  return view_type_;
}

ViewSettings::DisplayType ViewSettings::GetDisplayType(void) const {
  return display_type_;
}

ViewSettings::BlockSize ViewSettings::GetBlockSize(void) const {
  return block_size_;
}

void ViewSettings::SetViewType(ViewSettings::ViewType view_type) {
  view_type_ = view_type;
}

void ViewSettings::SetDisplayType(ViewSettings::DisplayType display_type) {
  display_type_ = display_type;
}

void ViewSettings::SetBlockSize(ViewSettings::BlockSize block_size) {
  block_size_ = block_size;
}
