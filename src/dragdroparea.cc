#include <QMimeData>
#include "dragdroparea.h"


DragDropArea::DragDropArea(QWidget *parent) : QLabel(parent)
{
  this->setAcceptDrops(true);
  this->setText(tr("Drag && Drop session file here."));
}


void DragDropArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void DragDropArea::dropEvent(QDropEvent* event)
 {
   const QMimeData* mimeData = event->mimeData();

   // check for our needed mime type, here a file or a list of files
   if (mimeData->hasUrls())
   {
     QList<QUrl> urlList = mimeData->urls();
     emit sessionFileDropped(urlList.at(0).toLocalFile());
   }
 }
