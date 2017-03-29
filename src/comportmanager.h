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
#include <QList>

#include "src/comport.h"
#include "src/localcomport.h"
#include "src/comportsettings.h"
#include "src/dataparser.h"

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
  void Receive(DataPacket&);

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
  void OnStartManualSequence(DataParser::ParserType eParser, QString str,
                             int repeat, int delay);

  //! Start dump sequence
  void OnStartDumpSequence(DataParser::ParserType eParser, QString path,
                           int repeat, int delay);

  //! Start auto sequence
  void OnStartAutoSequence(QString path);

  //! Stop sequence
  void OnStopSequence(void);

 private:
  //! Associated COM port
  ComPort* com_port_ {NULL};

  //! COM port settings
  ComPortSettings* com_port_settings_ {NULL};

  //! Manual mode str
  QString sequence_str_;

  //! Sequence timer
  QTimer* sequence_timer_ {nullptr};

  //! Sequence global repeat value
  int sequence_repeat_ {0};

  //! Current repeat value
  int pending_repeat_ {0};

  //! File path
  QString sequence_file_;

  //! Sequence in progress indicator
  bool sequence_in_progress_ {false};

  //! Frame list
  QList<QString> frame_list_;

  //! List index
  int list_idx_ {0};

  //! Global frame number
  int global_frame_nbr_ {0};

  //! Pending frame number
  int pending_frame_nbr_ {0};
};

#endif  // SRC_COMPORTMANAGER_H_
