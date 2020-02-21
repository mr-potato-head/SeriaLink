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

#include <QMimeData>
#include "src/dragdroparea.h"

DragDropArea::DragDropArea(QWidget *parent) : QWidget(parent) {
  dragdrop_label_ = new QLabel(tr("Drag & Drop session file here."), this);
  font_ = new QFont();
  font_->setPointSize(20);
  dragdrop_label_->setFont(*font_);
  dragdrop_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  dragdrop_icon_ = new QLabel(this);
  dragdrop_picture_ = new QPixmap();
  dragdrop_picture_->load(":/icons/icons/data-transfer-upload-8x.png");
  dragdrop_icon_->setPixmap(*dragdrop_picture_);
  dragdrop_icon_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  main_layout_ = new QGridLayout(parent);
  main_layout_->addWidget(dragdrop_label_, 1, 0);
  main_layout_->addWidget(dragdrop_icon_, 2, 0);
  main_layout_->setRowStretch(0,30);
  main_layout_->setRowStretch(1,20);
  main_layout_->setRowStretch(2,20);
  main_layout_->setRowStretch(3,30);

  this->setLayout(main_layout_);
  this->setAcceptDrops(true);
}

DragDropArea::~DragDropArea() {
  delete dragdrop_picture_;
  delete font_;
}

void DragDropArea::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls())
      event->acceptProposedAction();
}

void DragDropArea::dropEvent(QDropEvent* event) {
  const QMimeData* mimeData = event->mimeData();

  // check for our needed mime type, here a file or a list of files
  if (mimeData->hasUrls()) {
    QList<QUrl> urlList = mimeData->urls();
    emit fileDropped(urlList.at(0).toLocalFile());
  }
}
