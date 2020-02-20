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

#include "src/comport.h"

ComPort::ComPort(QObject *parent) :
  QObject(parent) {
}

void ComPort::SetPortSettings(ComPortSettings* port_settings) {
  com_port_settings_ = port_settings;
}

ComPortSettings* ComPort::GetPortSettings(void) {
  return com_port_settings_;
}

ComPort::PortType ComPort::GetPortType(void) const {
  return port_type_;
}
