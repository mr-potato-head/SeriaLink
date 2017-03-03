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

#include "src/sessionmanager.h"
#include "src/datapacket.h"

SessionManager::SessionManager(QObject *parent) :
  QObject(parent) {
  // Create default session
  Session* default_session = new Session();
  session_list_.append(default_session);

  // Initialize current session index
  current_session_index_ = 0;

  // Register metatypes
  qRegisterMetaType<DataPacket>("DataPacket");
}

SessionManager::~SessionManager() {
  QList<Session*>::iterator itBegin = session_list_.begin();
  QList<Session*>::iterator itEnd = session_list_.end();
  for (QList<Session*>::iterator it = itBegin ; it != itEnd ; it++) {
    (*it)->Close();
    delete *it;
  }
}

Session* SessionManager::GetCurrentSession(void) const {
  return session_list_.at(current_session_index_);
}
