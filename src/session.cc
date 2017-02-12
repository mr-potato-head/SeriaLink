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

#include "src/session.h"

Session::Session(QObject *parent)
  : QObject(parent) {
}

Session::~Session() {
    // Delete COM ports for this session
    QList<ComPort*>::iterator itBeginPort = com_port_list_.begin();
    QList<ComPort*>::iterator itEndPort = com_port_list_.end();
    for(QList<ComPort*>::iterator it = itBeginPort ; it != itEndPort ; it++) {
        delete *it;
    }

    // Delete threads for this session
    QList<QThread*>::iterator itBeginTh = thread_list_.begin();
    QList<QThread*>::iterator itEndTh = thread_list_.end();
    for(QList<QThread*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
        delete *it;
    }
}

void Session::AddPort(ComPortSettings* port_settings) {
  // Create new port
  LocalComPort* com_port = new LocalComPort();
  com_port_list_.append(com_port);
  com_port->SetPortSettings(port_settings);

  // Create thread for this port
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  com_port->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  current_port_index_ = com_port_list_.size()-1;
  emit PortAdded(current_port_index_);
}

ComPort* Session::GetPort(qint32 index) {
  return com_port_list_.at(index);
}

ComPort* Session::GetCurrentPort(void) {
  return com_port_list_.at(current_port_index_);
}

void Session::SetCurrentPortIndex(qint32 index) {
  current_port_index_ = index;
  emit IndexChanged(index);
}

void Session::OpenPort(qint32 index) {
  ComPort* port = com_port_list_.at(index);
  connect(this, SIGNAL(OpenPortSignal()),
          port, SLOT(OpenPort()));
  emit OpenPortSignal();
}

void Session::ClosePort(qint32 index) {
  ComPort* port = com_port_list_.at(index);
  port->ClosePort();
}

quint8 Session::GetPageNumber(void) {
  return com_port_list_.size();
}

quint8 Session::GetCurrentPortIndex(void) {
  return current_port_index_;
}
