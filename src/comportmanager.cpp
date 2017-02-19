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

#include "src/comportmanager.h"

ComPortManager::ComPortManager(ComPortSettings *port_settings,
                               QObject *parent)
    : QObject(parent),
      com_port_settings_{port_settings} {
    com_port_ = new LocalComPort();
    com_port_->SetPortSettings(com_port_settings_);

    connect(com_port_, SIGNAL(Receive(const DataPacket&)),
            this, SIGNAL(Receive(const DataPacket&)));
}

ComPortManager::~ComPortManager() {
    if (com_port_->IsOpen())
        com_port_->ClosePort();
    delete com_port_;
    com_port_ = NULL;
}

ComPortSettings* ComPortManager::GetPortSettings(void) const {
    return com_port_settings_;
}

void ComPortManager::OpenPort(void) {
    com_port_->OpenPort();
}

void ComPortManager::ClosePort(void) {
    com_port_->ClosePort();
}
