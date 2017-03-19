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

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "src/sessionmanager.h"
#include "src/datapacket.h"

SessionManager::SessionManager(QObject *parent) :
  QObject(parent) {
  // Create default session
  default_session_ = new Session();
  session_list_.append(default_session_);

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

void SessionManager::LoadSessionFile(QString filepath) {
  QFile session_file(filepath);

  if (!session_file.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QByteArray json_data = session_file.readAll();
  QJsonDocument load_doc(QJsonDocument::fromJson(json_data));

  if (!load_doc.isNull()) {
    if (load_doc.isObject()) {
      // Create session
      session_list_.append(default_session_);

      // Pass JSON data session
      QJsonObject global_object = load_doc.object();
      if (global_object["session_pages"].isArray()) {
        QJsonArray session_pages = global_object["session_pages"].toArray();
        for (int page_idx = 0; page_idx < session_pages.size(); ++page_idx) {
          QJsonObject page_object = session_pages[page_idx].toObject();
          // Add ports in session
          QJsonArray port_array = page_object["page_ports"].toArray();
          for (int port_idx = 0; port_idx < port_array.size(); ++port_idx) {
            QJsonObject port_object = port_array[port_idx].toObject();
            default_session_->AddPort(port_object);
          }

          // Add ports in session
          QJsonArray view_array = page_object["page_views"].toArray();
          for (int view_idx = 0; view_idx < view_array.size(); ++view_idx) {
            QJsonObject view_object = view_array[view_idx].toObject();

          }
        }
      } else {
        qWarning("session_pages is not and array.");
      }
    } else {
      qWarning("Can't find JSON object in file.");
    }
  } else {
    qWarning("Can't parse session file.");
  }
}
