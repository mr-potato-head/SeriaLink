#include <QRegularExpression>
#include "src/dataparser.h"

const QString DataParser::kAsciiPattern = "^[\\x00-\\x7F]+$";
const QString DataParser::kHexPattern = "^(?:(0[xX][0-9a-fA-F]+)[-,;|]?)+$";
const QString DataParser::kDecPattern = "^(?:([0-9]+)[-,;|]?)+$";

DataParser::DataParser() {
}

bool DataParser::CheckString(ParserType eType, const QString& str) {
  bool ret = false;
  switch(eType) {
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
                             QByteArray& array) {
  bool ret = false;
  switch(eType) {
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

bool DataParser::ParseAsciiString(const QString& str, QByteArray& data) {
}

bool DataParser::CheckHexString(const QString& str) {
  QRegularExpression reg_exp(kHexPattern);
  QRegularExpressionMatch match = reg_exp.match(str);
  return match.hasMatch();
}

bool DataParser::ParseHexString(const QString& str, QByteArray& data) {
}

bool DataParser::CheckDecString(const QString& str) {
  QRegularExpression reg_exp(kDecPattern);
  QRegularExpressionMatch match = reg_exp.match(str);
  return match.hasMatch();
}

bool DataParser::ParseDecString(const QString& str, QByteArray& data) {
}
