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

#ifndef SRC_VIEWSETTINGDIALOG_H_
#define SRC_VIEWSETTINGDIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "src/viewsettings.h"

class ViewSettingDialog : public QDialog {
  Q_OBJECT

 public:
  enum class ActionType {
    kAdd = 0,
    kUpdate
  };

  //! Default constructor
  explicit ViewSettingDialog(ViewSettings* view_settings,
                             ActionType action_type,
                             QWidget *parent = 0);

 private slots: // NOLINT
  //! Slot called when window is accepted
  void FillViewSettings(void);

 private:
  //! Main grid layout
  QGridLayout* form_grid_layout_ {NULL};

  //! Button bar
  QDialogButtonBox* button_bar_ {NULL};

  //! View settings
  ViewSettings* view_settings_ {NULL};

  //! Label "View type"
  QLabel* view_type_label_ {NULL};

  //! Combo box port choice
  QComboBox* view_type_combobox_ {NULL};

  //! Label "Display type"
  QLabel* display_type_label_ {NULL};

  //! Combo box display type choice
  QComboBox* display_type_combobox_ {NULL};

  //! Label for block timeout
  QLabel* block_timeout_label_ {NULL};

  //! Spinbox  for block timeout
  QSpinBox* block_timeout_spinbox_ {NULL};

  //! Label for block size
  QLabel* block_size_label_ {NULL};

  //! Spinbox  for block size
  QSpinBox* block_size_spinbox_ {NULL};

  //! Fill view type comboBox
  void FillViewTypeList(void);

  //! Fill display type comboBox
  void FillDisplayTypeList(void);
};

#endif  // SRC_VIEWSETTINGDIALOG_H_
