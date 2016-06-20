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

#ifndef SRC_VIEWSETTINGS_H_
#define SRC_VIEWSETTINGS_H_

class ViewSettings {
 public:
  //! Type of the view
  enum class ViewType {
    kUnknown = 0,
    kTerminal,
    kTable,
    kDump
  };

  //! Data display mode
  enum class DisplayType {
    kUnknown = 0,
    kHexa,
    kAscii,
    kDec
  };

  //! Data block size
  enum class BlockSize {
    kUnknown = 0,
    k1Byte,
    k2Bytes,
    k4Bytes,
    k8Bytes
  };

  //! Default constructor
  ViewSettings();

  ViewType GetViewType(void) const;
  DisplayType GetDisplayType(void) const;
  BlockSize GetBlockSize(void) const;
  void SetViewType(ViewSettings::ViewType view_type);
  void SetDisplayType(ViewSettings::DisplayType display_type);
  void SetBlockSize(ViewSettings::BlockSize block_size);

 private:
  //! View type
  ViewType view_type_ {ViewType::kUnknown};

  //! Display type
  DisplayType display_type_ {DisplayType::kUnknown};

  //! Data block size
  BlockSize block_size_ {BlockSize::kUnknown};
};

#endif  // SRC_VIEWSETTINGS_H_
