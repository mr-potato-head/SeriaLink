/*
 * Copyright (C) 2020 Guilhem GUYONNET
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

#ifndef SRC_ABOUTWINDOW_H_
#define SRC_ABOUTWINDOW_H_

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>

class AboutWindow : public QDialog {
  Q_OBJECT

 public:
  //! Constructor
  explicit AboutWindow(QWidget* parent = nullptr);

 private:
  //! Version label
  QLabel* version_label_ {nullptr};

  //! Main grid layout
  QGridLayout* main_layout_ {nullptr};

  //! Button box
  QDialogButtonBox* button_box_ {nullptr};
};

#endif  // SRC_ABOUTWINDOW_H_
