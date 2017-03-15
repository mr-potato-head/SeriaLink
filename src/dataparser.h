#ifndef SRC_DATAPARSER_H_
#define SRC_DATAPARSER_H_

#include <QString>
#include <QByteArray>

class DataParser
{
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
                          QByteArray& array);

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
  static bool ParseAsciiString(const QString& str, QByteArray& data);

  //! Check if string follow hex
  static bool CheckHexString(const QString& str);

  //! Parser string to extract data to send
  static bool ParseHexString(const QString& str, QByteArray& data);

  //! Check if string follow dec
  static bool CheckDecString(const QString& str);

  //! Parser string to extract data to send
  static bool ParseDecString(const QString& str, QByteArray& data);
};

#endif // SRC_DATAPARSER_H_
