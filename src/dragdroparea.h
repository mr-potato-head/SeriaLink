#ifndef DRAGDROPAREA_H
#define DRAGDROPAREA_H

#include <QLabel>
#include <QDragEnterEvent>

class DragDropArea : public QLabel
{
    Q_OBJECT
  public:
    explicit DragDropArea(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent* event);

  signals:

    void sessionFileDropped(QString filepath);

  public slots:
};

#endif // DRAGDROPAREA_H
