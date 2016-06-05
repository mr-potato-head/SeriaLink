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

#ifndef SRC_SESSION_H_
#define SRC_SESSION_H_

#include <QList>
#include "src/comport.h"

class Session {
 public:
  //! Default constructor
  Session();

  //! Add port in this session
  qint32 AddPort(ComPort* port);

  //! Get port by index
  ComPort* GetPort(qint32 index);

 private:
  //! COM port list
  QList<ComPort*> com_port_list_;

  //! Index of the current port;
  qint8 current_port_index_ {-1};
};

#endif  // SRC_SESSION_H_
