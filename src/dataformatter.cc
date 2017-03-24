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

#include "src/dataformatter.h"

DataFormatter::DataFormatter() {}

QString DataFormatter::formatData(ViewSettings &settings,
                                  DataPacket& packet) {
  ViewSettings::DataSize eDataSize = settings.GetDataSize();
  ViewSettings::DisplayType eDisplayType = settings.GetDisplayType();

  qint8 qint8_size = 0;
  switch (eDataSize) {
  case ViewSettings::DataSize::k1Byte:
    qint8_size = 1;
    break;
  case ViewSettings::DataSize::k2Bytes:
    qint8_size = 2;
    break;
  case ViewSettings::DataSize::k4Bytes:
    qint8_size = 4;
    break;
  case ViewSettings::DataSize::k8Bytes:
    qint8_size = 8;
    break;
  case ViewSettings::DataSize::kNoSize:
  case ViewSettings::DataSize::kUnknown:
  default:
    qint8_size = -1;
    break;
  }

  QString out;
  if (qint8_size != -1) {
    out += "|";
  }
  quint32 quint32_index = 0;
  quint32 quint32_datasize = packet.GetData().size();
  for (; quint32_index < quint32_datasize ; quint32_index+=qint8_size) {
    QByteArray dataBlock = packet.GetData().mid(quint32_index, qint8_size);
    switch (eDisplayType) {
    case ViewSettings::DisplayType::kAscii:
      dataBlock = dataBlock.replace("\r", "\\r");
      dataBlock = dataBlock.replace("\n", "\\n");
      out += QString(dataBlock);
      break;
    case ViewSettings::DisplayType::kHexa:
      out += QString(dataBlock.toHex().toUpper());
      break;
    case ViewSettings::DisplayType::kDec:
    {
      bool coucou = false;
      out += QString::number(dataBlock.toHex().toUInt(&coucou, 16));
      break;
    }
    default:
      break;
    }
    if (qint8_size != -1) {
      out += "|";
    }
  }
  return out;
}
