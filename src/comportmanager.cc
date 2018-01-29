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
#include "src/comportmanager.h"
#include "src/dataparser.h"

ComPortManager::ComPortManager(ComPortSettings *port_settings,
                               QObject *parent)
  : QObject(parent),
    com_port_settings_{port_settings} {
  qRegisterMetaType<DataParser::ParserType>("DataParser::ParserType");
}

ComPortManager::~ComPortManager() {
  ClosePort();
  delete com_port_settings_;
}

ComPortSettings* ComPortManager::GetPortSettings(void) const {
  return com_port_settings_;
}

void ComPortManager::OpenPort(void) {
  com_port_ = new LocalComPort(this);
  com_port_->SetPortSettings(com_port_settings_);

  connect(com_port_, SIGNAL(DataReceived(DataPacket)),
          this, SIGNAL(DataReceived(DataPacket)));

  connect(com_port_, SIGNAL(DataSent(DataPacket)),
          this, SIGNAL(DataSent(DataPacket)));

  connect(com_port_, SIGNAL(PortOpened()),
          this, SIGNAL(PortOpened()));

  connect(com_port_, SIGNAL(PortClosed()),
          this, SIGNAL(PortClosed()));

  connect(com_port_, SIGNAL(PortErrorOccurred(QSerialPort::SerialPortError)),
          this, SIGNAL(PortErrorOccurred(QSerialPort::SerialPortError)));

  com_port_->OpenPort();
}

void ComPortManager::ClosePort(void) {
  // Stop current sequence
  if (sequence_in_progress_) {
    this->OnStopSequence();
  }

  // Close port
  if (com_port_) {
    com_port_->ClosePort();
    delete com_port_;
    com_port_ = NULL;
  }
}

void ComPortManager::OnStartManualSequence(DataParser::ParserType eParser,
                                           QString str, int repeat,
                                           int delay) {
  // Save data
  sequence_str_ = str;
  sequence_repeat_ = repeat;
  pending_repeat_ = repeat;

  // Send first frame
  QByteArray data;
  // TODO(Guilhem): check result
  DataParser::ParseString(eParser, str, &data);
  DataPacket packet(data);
  com_port_->Send(packet);
  pending_repeat_--;

  double progress = static_cast<double>(sequence_repeat_ - pending_repeat_)/
                    static_cast<double>(sequence_repeat_);
  //emit SequenceProgress(static_cast<int>(progress*100.0));

  // Check if a sequence has been requested
  if (pending_repeat_ > 0) {
    sequence_in_progress_ = true;
    sequence_timer_ = new QTimer(this);
    sequence_timer_->setSingleShot(false);
    sequence_timer_->setInterval(delay);
    connect(sequence_timer_, &QTimer::timeout, [=](void) {
      QByteArray data;
      // TODO(Guilhem): check result
      DataParser::ParseString(eParser, str, &data);
      DataPacket packet(data);
      com_port_->Send(packet);
      pending_repeat_--;

      double progress = static_cast<double>(sequence_repeat_ - pending_repeat_)/
                        static_cast<double>(sequence_repeat_);
      emit SequenceProgress(static_cast<int>(progress*100.0));

      if (pending_repeat_ == 0) {
        sequence_in_progress_ = false;
        sequence_timer_->stop();
        delete sequence_timer_;
        sequence_timer_ = nullptr;
        emit SequenceOver();
      }
    });
    sequence_timer_->start();
  } else {
    sequence_in_progress_ = false;
    emit SequenceOver();
  }
}

void ComPortManager::OnStartDumpSequence(DataParser::ParserType eParser,
                                         QString path, int repeat,
                                         int delay) {
  // Load file
  frame_list_.clear();
  sequence_file_ = path;
  QFile file(sequence_file_);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    emit SequenceOver();
    return;
  }

  QTextStream in(&file);
  while (!in.atEnd()) {
    frame_list_.append(in.readLine());
  }

  // Init frame number
  global_frame_nbr_ = frame_list_.size() * repeat;
  pending_frame_nbr_ = global_frame_nbr_;

  sequence_in_progress_ = true;

  // Send first frame
  QByteArray data;
  // TODO(Guilhem): check result
  DataParser::ParseString(eParser, frame_list_.at(list_idx_), &data);
  DataPacket packet(data);
  com_port_->Send(packet);
  pending_frame_nbr_--;
  list_idx_++;

  double progress = static_cast<double>(global_frame_nbr_ - pending_frame_nbr_)/
                    static_cast<double>(global_frame_nbr_);
  emit SequenceProgress(static_cast<int>(progress*100.0));

  if (pending_frame_nbr_ > 0) {
    sequence_in_progress_ = true;
    sequence_timer_ = new QTimer(this);
    sequence_timer_->setSingleShot(false);
    sequence_timer_->setInterval(delay);
    connect(sequence_timer_, &QTimer::timeout, [=](void) {
      QByteArray data;
      // TODO(Guilhem): check result
      DataParser::ParseString(eParser, frame_list_.at(list_idx_), &data);
      DataPacket packet(data);
      com_port_->Send(packet);
      pending_frame_nbr_--;
      list_idx_++;

      if (list_idx_ == frame_list_.size()) {
        list_idx_ = 0;
      }

      double progress = static_cast<double>(global_frame_nbr_ -
                                            pending_frame_nbr_)/
                        static_cast<double>(global_frame_nbr_);
      emit SequenceProgress(static_cast<int>(progress*100.0));

      if (pending_frame_nbr_ == 0) {
        sequence_in_progress_ = false;
        sequence_timer_->stop();
        delete sequence_timer_;
        sequence_timer_ = nullptr;
        emit SequenceOver();
      }
    });
    sequence_timer_->start();
  }
}

void ComPortManager::OnStartAutoSequence(QString path) {}

void ComPortManager::OnStopSequence(void) {
  frame_list_.clear();
  sequence_in_progress_ = false;
  sequence_timer_->stop();
  delete sequence_timer_;
  sequence_timer_ = nullptr;
}
