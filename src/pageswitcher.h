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

#ifndef SRC_PAGESWITCHER_H_
#define SRC_PAGESWITCHER_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class PageSwitcher : public QWidget {
  Q_OBJECT

 public:
  //! Button type
    enum class ButtonType {
      kDecreaseButton = 0,
      kAddButton,
      kIncreaseButton
    };

  //! Default constructor
  explicit PageSwitcher(QWidget *parent = 0);

  //! Enable button
  void EnableButton(ButtonType type);

  //! Disable button
  void DisableButton(ButtonType type);

 signals:
  //! Signal emitted when left button is clicked
  void DecreaseCurrentPageIndex(void);

  //! Signal emitted when right button is clicked
  void IncreaseCurrentPageIndex(void);

  //! Signal emitted when add button is clicked
  void AddPage(void);

  //! Open menu signal
  void OpenMenu(void);

 private:
  //! Main horizontal layout of the widget
  QHBoxLayout* main_layout_ {NULL};

  //! Button to switch to the next right page
  QPushButton* right_button_ {NULL};

  //! Button to switch to the next left page
  QPushButton* left_button_ {NULL};

  //! Button to add new page
  QPushButton* add_button_ {NULL};

  //! Menu button
  QPushButton* menu_button_ {NULL};

  //! Vertical line
  QWidget* vertical_line_ {NULL};
};

#endif  // SRC_PAGESWITCHER_H_
