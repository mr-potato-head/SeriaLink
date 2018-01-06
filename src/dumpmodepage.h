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

#ifndef SRC_DUMPMODEPAGE_H_
#define SRC_DUMPMODEPAGE_H_

#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include "src/modepage.h"

class DumpModePage : public ModePage {
 public:
  //! Constructor
  explicit DumpModePage(QWidget *parent = 0);

 private slots: //NOLINT
  //! Click on send button reaction
  void OnStartButtonClicked(void);

 private:
  //! Manual mode data line
  QLineEdit* path_line_ {nullptr};

  //! Browse button
  QPushButton* browse_button_ {nullptr};

  //! Path layout
  QHBoxLayout* path_layout_ {nullptr};

  //! Manual mode loop group box
  QGroupBox* loop_groupbox_ {nullptr};

  //! Parser choice group box
  QGroupBox* parser_groupbox_ {nullptr};

  //! Radio button "ASCII"
  QRadioButton* ascii_radio_ {nullptr};

  //! Radio button "HEX"
  QRadioButton* hex_radio_ {nullptr};

  //! Radio button "DEC"
  QRadioButton* dec_radio_ {nullptr};

  //! Parser vertical layout
  QVBoxLayout* parser_layout_ {nullptr};

  //! Grid layout of the loop groupbox
  QGridLayout* loop_layout_ {nullptr};

  //! Label "Delay"
  QLabel* delay_label_ {nullptr};

  //! Label "ms"
  QLabel* ms_label_ {nullptr};

  //! Label "Repeat"
  QLabel* repeat_label_ {nullptr};

  //! Label "frames"
  QLabel* frames_label_ {nullptr};

  //! Delay spinbox
  QSpinBox* delay_spinbox_ {nullptr};

  //! Frame number splinbox
  QSpinBox* repeat_spinbox_ {nullptr};

  //! Vertical line
  QWidget* vertical_line_ {nullptr};
};

#endif  // SRC_DUMPMODEPAGE_H_
