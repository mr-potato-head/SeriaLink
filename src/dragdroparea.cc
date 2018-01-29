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

#include <QMimeData>
#include "src/dragdroparea.h"

DragDropArea::DragDropArea(QWidget *parent) : QLabel(parent) {
  this->setAcceptDrops(true);
  this->setText(tr("Drag && Drop session file here."));
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
