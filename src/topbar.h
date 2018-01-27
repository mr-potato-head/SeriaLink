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

#ifndef SRC_TOPBAR_H_
#define SRC_TOPBAR_H_

#include <QWidget>
#include <QHBoxLayout>
#include "src/pageswitcher.h"
#include "src/pageselector.h"

class Session;

class TopBar : public QWidget {
  Q_OBJECT

 public:
  //! Default constructor
  explicit TopBar(QWidget *parent = 0);

  //! Set pointer on session
  void SetSession(Session* session);

  void AddPageButton(void);

  void DeletePageButton(int page_idx);

  void UpdatePageButtonName(int page_idx);

  //! Update page switcher button status
  void UpdateSwitcherButtonStatus(void);

  //! Update page selector button status
  void UpdateSelectorButtonStatus(void);

 signals:
  //! Signal emitted when index is updated
  void PageIndexUpdated(qint8);

  //! Open menu signal
  void OpenMenu(void);

 private slots:  // NOLINT
  //! Slots called when page index should be increased
  void OnIncreaseCurrentPageIndex(void);

  //! Slots called when page index should be decreased
  void OnDecreaseCurrentPageIndex(void);

  //! Slots called when add button is clicked
  void openAddOrModifyDialog(void);

 private:
  //! Main layout of the widget
  QHBoxLayout* main_layout_ {NULL};

  //! Page selector with COM port buttons
  PageSelector* page_selector_ {NULL};

  //! Page switcher widget
  PageSwitcher* page_switcher_ {NULL};

  //! Pointer on session
  Session* session_ {NULL};
};

#endif  // SRC_TOPBAR_H_
