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

#ifndef SRC_DATAPACKET_H_
#define SRC_DATAPACKET_H_

#include <QByteArray>
#include <QDateEdit>

class DataPacket {
 public:
  DataPacket();
  explicit DataPacket(const QByteArray& data);
  const QByteArray& GetData(void) const;
  const QDateTime& GetDateTime(void) const;
 private:
  QByteArray data_;
  QDateTime datetime_;
};

#endif  // SRC_DATAPACKET_H_
