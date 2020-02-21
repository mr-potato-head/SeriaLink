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

#ifndef SRC_DRAGDROPAREA_H_
#define SRC_DRAGDROPAREA_H_

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QDragEnterEvent>

class DragDropArea : public QWidget {
  Q_OBJECT
 public:
  explicit DragDropArea(QWidget *parent = nullptr);
 virtual ~DragDropArea();

  void dragEnterEvent(QDragEnterEvent *event);

  void dropEvent(QDropEvent* event);

 signals:

  void fileDropped(QString filepath);

 private:
  //! Vertical layout
  QGridLayout* main_layout_ {nullptr};

  //! Drag & Drop text
  QLabel* dragdrop_label_ {nullptr};

  //! Drag & Drop icon
  QLabel* dragdrop_icon_ {nullptr};

  //! Icon for Drag & Drop
  QPixmap* dragdrop_picture_ {nullptr};

  //! Font for drag & drop text
  QFont* font_ {nullptr};
};

#endif  // SRC_DRAGDROPAREA_H_
