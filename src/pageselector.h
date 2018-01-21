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

#ifndef SRC_PAGESELECTOR_H_
#define SRC_PAGESELECTOR_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QSignalMapper>
#include <QPushButton>

class Session;

class PageSelector : public QWidget {
  Q_OBJECT

 public:
  //! Default constructor
  explicit PageSelector(QWidget *parent = 0);

  //! Set session pointer
  void SetSession(Session* session);

  //! Set checked state for a button
  void SetCheckedState(qint32 page_index);

  void UpdateButtonName(quint8 page_idx);

 public slots: // NOLINT
  //! Add button
  void AddButton();

 private:
  //! Button list
  QList<QPushButton*> button_list_;

  //! Button layout
  QHBoxLayout* button_layout_ {NULL};

  //! Pointer on session
  Session* session_ {NULL};

  //! Signal mapper for buttons
  QSignalMapper* signal_mapper_ {NULL};
};

#endif  // SRC_PAGESELECTOR_H_
