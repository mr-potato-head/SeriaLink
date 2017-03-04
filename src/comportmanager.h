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

#ifndef SRC_COMPORTMANAGER_H_
#define SRC_COMPORTMANAGER_H_

#include <QObject>
#include <QTimer>

#include "src/comport.h"
#include "src/localcomport.h"
#include "src/comportsettings.h"

class ComPortManager : public QObject {
  Q_OBJECT

 public:

  //! Constructor
  explicit ComPortManager(ComPortSettings* port_settings,
                          QObject* parent = 0);

  //! Destructor
  ~ComPortManager();

  //! Get port settings
  ComPortSettings* GetPortSettings(void) const;

 signals:
  //! Emitted when new data are received
  void Receive(const DataPacket&);

  //! Emitted to inform GUI on sequence progression
  void SequenceProgress(int);

  //! Emitted when sequence is over
  void SequenceOver(void);

 public slots: //NOLINT
  //! Open COM port
  void OpenPort(void);

  //! Close COM port
  void ClosePort(void);

  //! Start manual sequence
  void OnStartManualSequence(QString data, int repeat, int delay);

  //! Start dump sequence
  void OnStartDumpSequence(QString path, int repeat, int delay);

  //! Start auto sequence
  void OnStartAutoSequence(QString path);

  //! Stop sequence
  void OnStopSequence(void);

 private:
  //! Associated COM port
  ComPort* com_port_ {NULL};

  //! COM port settings
  ComPortSettings* com_port_settings_ {NULL};

  //! Manual mode data
  QString sequence_data_;

  //! Sequence timer
  QTimer* sequence_timer_ {nullptr};

  //! Sequence global repeat value
  int sequence_repeat_ {0};

  //! Current repeat value
  int pending_repeat_ {0};

  //! Sequence in progress indicator
  bool sequence_in_progress_ {false};
};

#endif  // SRC_COMPORTMANAGER_H_
