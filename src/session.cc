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
    QList<ComPortManager*>::iterator itBeginPort = com_port_mgr_list_.begin();
    QList<ComPortManager*>::iterator itEndPort = com_port_mgr_list_.end();
    for(QList<ComPortManager*>::iterator it = itBeginPort ; it != itEndPort ; it++) {
        delete *it;
    }

    // Delete threads for this session
    QList<QThread*>::iterator itBeginTh = thread_list_.begin();
    QList<QThread*>::iterator itEndTh = thread_list_.end();
    for(QList<QThread*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
        (*it)->quit();
        if(!(*it)->wait(1000)) {
            qDebug() << "Timeout arret du thread.";
        }
        delete *it;
    }
}

void Session::AddPort(ComPortSettings* port_settings) {
  // Create new port manager
  ComPortManager* com_port_mgr = new ComPortManager(port_settings);
  com_port_mgr_list_.append(com_port_mgr);

  // Create thread for this port manager
  QThread* thread = new QThread(this);
  thread_list_.append(thread);
  com_port_mgr->moveToThread(thread);
  thread->start(QThread::TimeCriticalPriority);

  current_port_mgr_index_ = com_port_mgr_list_.size()-1;
  emit PortAdded(current_port_mgr_index_);
}

void Session::SetCurrentPortMgrIndex(qint32 index) {
  current_port_mgr_index_ = index;
  emit IndexChanged(index);
}

void Session::OpenPort(qint32 index) {
  ComPortManager* port_mgr = com_port_mgr_list_.at(index);
  port_mgr->OpenPort();
}

void Session::ClosePort(qint32 index) {
    ComPortManager* port_mgr = com_port_mgr_list_.at(index);
    port_mgr->ClosePort();
}

quint8 Session::GetPortNumber(void) {
  return com_port_mgr_list_.size();
}

quint8 Session::GetCurrentPortMgrIndex(void) {
  return current_port_mgr_index_;
}

ComPortManager* Session::GetPortManager(qint32 index) {
    return com_port_mgr_list_.at(index);
}
