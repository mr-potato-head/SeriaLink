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

#ifndef SRC_ADDORMODIFYPORTDIALOG_H_
#define SRC_ADDORMODIFYPORTDIALOG_H_

#include <QDialog>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "src/comportsettings.h"

class AddOrModifyPortDialog : public QDialog {
  Q_OBJECT

 public:
  enum class ActionType {
    kAdd = 0,
    kUpdate
  };

  //! Default constructor
  explicit AddOrModifyPortDialog(ComPortSettings* port_settings,
                                 ActionType action_type,
                                 QWidget *parent = 0);

 private slots: // NOLINT
  //! Slot called when update button is clicked
  void FillPortList(void);

  //! Slot called when window is accepted
  void FillPortSettings(void);

 private:
  //! Form grid layout
  QGridLayout* form_grid_layout_ {NULL};

  //! Label "Port"
  QLabel* port_label_ {NULL};

  //! Combo box port choice
  QComboBox* port_combobox_ {NULL};

  //! Update port list button
  QPushButton* port_list_upd_button_ {NULL};

  //! Port HBox layout
  QHBoxLayout* port_hbox_layout_ {NULL};

  //! Label "Baud rate"
  QLabel* baud_rate_label_ {NULL};

  //! Combo box baud rate choice
  QComboBox* baudrate_combobox_ {NULL};

  //! Label "Parity"
  QLabel* parity_label_ {NULL};

  //! Combo box parity choice
  QComboBox* parity_combobox_ {NULL};

  //! Label "Data bits"
  QLabel* data_bits_label_ {NULL};

  //! Combo box data bits choice
  QComboBox* data_bits_combobox_ {NULL};

  //! Label "Stop bits"
  QLabel* stop_bits_label_ {NULL};

  //! Combo box stop bits choice
  QComboBox* stop_bits_combobox_ {NULL};

  //! Label "Flow control"
  QLabel* flow_control_label_ {NULL};

  //! Combo box flow control choice
  QComboBox* flow_control_combobox_ {NULL};

  //! Button bar
  QDialogButtonBox* button_bar_ {NULL};

  //! Pointer on port settings
  ComPortSettings* port_settings_ {NULL};

  //! Fill parity comboBox
  void FillParityList(void);

  //! Fill baud rate comboBox
  void FillBaudRateList(void);

  //! Fill data bits comboBox
  void FillDataBitsList(void);

  //! Fill Stop bits comboBox
  void FillStopBitsList(void);

  //! Fill flow control comboBox
  void FillFlowControlList(void);
};

#endif  // SRC_ADDORMODIFYPORTDIALOG_H_
