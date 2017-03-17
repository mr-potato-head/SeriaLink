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

#ifndef SRC_DATAPARSER_H_
#define SRC_DATAPARSER_H_

#include <QString>
#include <QByteArray>

class DataParser {
 public:
  //! Parser type
  enum class ParserType {
    kUnknown = 0,
    kAscii,
    kHex,
    kDec
  };

  //! Constructor
  DataParser();

  //! Check if string follow parser type
  static bool CheckString(ParserType eType, const QString& str);

  //! Parser string to extract data to send
  static bool ParseString(ParserType eType, const QString& str,
                          QByteArray* array);

 private:
  //! RegExp for ASCII strings
  static const QString kAsciiPattern;

  //! RegExp for Hex strings
  static const QString kHexParsePattern;

  //! RegExp for Hex strings
  static const QString kHexCheckPattern;

  //! RegExp for Dec strings
  static const QString kDecParsePattern;

  //! RegExp for Dec strings
  static const QString kDecCheckPattern;

  //! Check if string follow ascii
  static bool CheckAsciiString(const QString& str);

  //! Parser string to extract data to send
  static bool ParseAsciiString(const QString& str, QByteArray* data);

  //! Check if string follow hex
  static bool CheckHexString(const QString& str);

  //! Parser string to extract data to send
  static bool ParseHexString(const QString& str, QByteArray* data);

  //! Check if string follow dec
  static bool CheckDecString(const QString& str);

  //! Parser string to extract data to send
  static bool ParseDecString(const QString& str, QByteArray* data);
};

#endif  // SRC_DATAPARSER_H_
