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

#ifndef SRC_PORTVIEW_H_
#define SRC_PORTVIEW_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include "src/viewsettings.h"
#include "src/datapacket.h"

class PortView : public QWidget {
  Q_OBJECT

 public:
  //! Constructeur
  PortView(ViewSettings* view_settings,
           QWidget *parent = 0);

  //! Destruteur
  ~PortView(void);

  //! Get view settings
  ViewSettings* GetViewSettings(void);

 signals:
  //! Emitted when delete button has been clicked
  void DeleteView(PortView*);

 public slots: //NOLINT
  //! Executed when new data are received
  virtual void TreatDataPacket(DataPacket packet) = 0;

  //! Executed when new data are received
  virtual void OnDataSent(DataPacket packet) = 0;

  //! Executed when data are received
  void OnReceivedData(QByteArray data);

 protected:
  //! Main grid layout of the view
  QGridLayout* main_layout_ {NULL};

  //! Clear button
  QPushButton* clear_button_ {nullptr};

  //! Settings of the view
  ViewSettings* view_settings_ {nullptr};

  //! Is capture in progress
  bool capture_in_progress_ {false};

  //! Text stream of capture file
  QTextStream* capture_stream_ {nullptr};

 private slots: //NOLINT
  //! Executed when received timer timeout occurred
  void OnTimeout(void);

 private:
  //! Horizontal layout of up buttons
  QHBoxLayout* button_layout_ {nullptr};

  //! Delete button
  QPushButton* delete_button_ {nullptr};

  //! Edit button
  QPushButton* edit_button_ {nullptr};

  //! Spacer item
  QSpacerItem* spacer_item_ {nullptr};

  //! Capture group box
  QGroupBox* capture_groupbox_ {nullptr};

  //! Capture groupbox grid layout
  QGridLayout* capture_layout_ {nullptr};

  //! Spacer item of the capture groupbox
  QSpacerItem* cap_spacer_item_ {nullptr};

  //! Open button
  QPushButton* open_button_ {nullptr};

  //! Browse button
  QPushButton* browse_button_ {nullptr};

  //! Record start button
  QPushButton* start_rec_button_ {nullptr};

  //! Record stop button
  QPushButton* stop_rec_button_ {nullptr};

  //! Append radiobutton
  QRadioButton* append_button_ {nullptr};

  //! Overwrite radiobutton
  QRadioButton* overwrite_button_ {nullptr};

  //! Radio button layout
  QHBoxLayout* file_mode_layout_ {nullptr};

  //! File path
  QLineEdit* file_path_ {nullptr};

  //! Pointer on capture file
  QFile* capture_file_ {nullptr};

  //! Receive timeout timer
  QTimer* receive_timer_ {nullptr};

  //! Current data packet
  DataPacket data_packet_;

  //! Waiting for more data indicator
  bool waiting_data_ {false};
};

#endif  // SRC_PORTVIEW_H_
