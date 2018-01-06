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

#include <QRegularExpression>
#include <QDebug>
#include "src/dataparser.h"

const QString DataParser::kAsciiPattern = "^[\\x00-\\x7F]+$";
const QString DataParser::kHexCheckPattern = "^(?:0[xX][0-9a-fA-F]+[-,;|]?)+$";
const QString DataParser::kHexParsePattern = "0[xX]([0-9a-fA-F]+)[-,;|]?";
const QString DataParser::kDecCheckPattern = "^(?:([0-9]+)[-,;|]?)+$";
const QString DataParser::kDecParsePattern = "([0-9]+)[-,;|]?";

DataParser::DataParser() {
}

bool DataParser::CheckString(ParserType eType, const QString& str) {
  bool ret = false;
  switch (eType) {
  case ParserType::kAscii:
    ret = CheckAsciiString(str);
    break;
  case ParserType::kHex:
    ret = CheckHexString(str);
    break;
  case ParserType::kDec:
    ret = CheckDecString(str);
    break;
  case ParserType::kUnknown:
  default:
    ret = false;
    break;
  }
  return ret;
}

bool DataParser::ParseString(ParserType eType,
                             const QString& str,
                             QByteArray* array) {
  bool ret = false;
  switch (eType) {
  case ParserType::kAscii:
    ret = ParseAsciiString(str, array);
    break;
  case ParserType::kHex:
    ret = ParseHexString(str, array);
    break;
  case ParserType::kDec:
    ret = ParseDecString(str, array);
    break;
  case ParserType::kUnknown:
  default:
    ret = false;
    break;
  }
  return ret;
}

bool DataParser::CheckAsciiString(const QString& str) {
  QRegularExpression reg_exp(kAsciiPattern);
  QRegularExpressionMatch match = reg_exp.match(str);
  return match.hasMatch();
}

bool DataParser::ParseAsciiString(const QString& str, QByteArray* data) {
  *data = str.toUtf8();
  return true;
}

bool DataParser::CheckHexString(const QString& str) {
  QRegularExpression reg_exp(kHexCheckPattern);
  QRegularExpressionMatch match = reg_exp.match(str);
  return match.hasMatch();
}

bool DataParser::ParseHexString(const QString& str, QByteArray* data) {
  QRegularExpression reg_exp(kHexParsePattern);
  QRegularExpressionMatchIterator i = reg_exp.globalMatch(str);
  while (i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    bool error = false;
    data->append(match.captured(1).toUInt(&error, 16));
  }
  return true;
}

bool DataParser::CheckDecString(const QString& str) {
  QRegularExpression reg_exp(kDecCheckPattern);
  QRegularExpressionMatch match = reg_exp.match(str);
  return match.hasMatch();
}

bool DataParser::ParseDecString(const QString& str, QByteArray* data) {
  QRegularExpression reg_exp(kDecParsePattern);
  QRegularExpressionMatchIterator i = reg_exp.globalMatch(str);
  while (i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    bool error = false;
    data->append(match.captured(1).toUInt(&error, 10));
  }
  return true;
}
