/*
 * Copyright (C) 2020 Guilhem GUYONNET
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

QString DataFormatter::formatData(ViewSettings settings,
                                  DataPacket packet) {
  ViewSettings::DisplayType eDisplayType = settings.GetDisplayType();

  QString out;
  QByteArray dataBlock = packet.GetData();
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
    bool ok = false;
    out += QString::number(dataBlock.toHex().toUInt(&ok, 16));
    break;
  }
  default:
    break;
  }

  return out;
}
