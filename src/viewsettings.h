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

#include <QMap>
#include <QJsonObject>

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

  //! Data data size
  enum class DataSize {
    kUnknown = 0,
    kNoSize,
    k1Byte,
    k2Bytes,
    k4Bytes,
    k8Bytes
  };

  //! Default constructor
  ViewSettings();

  //! Constructor with json object
  explicit ViewSettings(QJsonObject view_object);

  //! Get view type
  ViewType GetViewType(void);

  //! Get display type
  DisplayType GetDisplayType(void) const;

  //! Get data size
  DataSize GetDataSize(void) const;

  //! Get end of data block timeout
  int GetDataBlockTimeout(void) const;

  //! Get data block size
  int GetDataBlockSize(void) const;

  //! Set view type
  void SetViewType(ViewSettings::ViewType view_type);

  //! Set display type
  void SetDisplayType(ViewSettings::DisplayType display_type);

  //! Set data size
  void SetDataSize(ViewSettings::DataSize data_size);

  //! Set data block size
  void SetDataBlockSize(int data_block_size);

  //! Set data block timeout;
  void SetDataBlockTimeout(int data_block_timeout);

  //! Get JSON translation
  QJsonObject ToJson(void);

 private:
  //! Map ViewType<>JsonStrViewType
  static const QMap<QString, ViewSettings::ViewType> kViewTypeFromString;

  //! Map ViewType<>JsonStrDisplayType
  static const QMap<QString, ViewSettings::DisplayType> kDisplayTypeFromString;

  //! Map ViewType<>JsonStrSize
  static const QMap<QString, ViewSettings::DataSize> kDataSizeFromString;

  //! Map ViewType<>JsonStrViewType
  static const QMap<ViewSettings::ViewType, QString> kStringFromViewType;

  //! Map ViewType<>JsonStrDisplayType
  static const QMap<ViewSettings::DisplayType, QString> kStringFromDisplayType;

  //! Map ViewType<>JsonStrSize
  static const QMap<ViewSettings::DataSize, QString> kStringFromDataSize;

  //! View type
  ViewType view_type_ {ViewType::kUnknown};

  //! Display type
  DisplayType display_type_ {DisplayType::kUnknown};

  //! Data block size
  DataSize data_size_ {DataSize::kUnknown};

  //! Timeout for data packet
  int data_block_timeout_ {5000};

  //! Data block size
  int data_block_size_ {10};
};

#endif  // SRC_VIEWSETTINGS_H_
