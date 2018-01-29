#ifndef PORTINFOAREAWIDGET_H
#define PORTINFOAREAWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include "src/comportmanager.h"
#include "src/portinfowidget.h"

class Session;

class PortInfoAreaWidget : public QScrollArea
{
    Q_OBJECT
  public:
    explicit PortInfoAreaWidget(Session* session, int page_idx, QWidget *parent = 0);

    void AddPort(int port_idx);

    void DeletePort(int port_idx);

  signals:

  public slots:

  private:

  QVBoxLayout* main_layout_ {nullptr};

  Session* session_ {nullptr};

  QList<PortInfoWidget*> port_info_widget_list_;

  int page_idx_ {0};
};

#endif // PORTINFOAREAWIDGET_H