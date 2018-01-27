#include "portinfoareawidget.h"

PortInfoAreaWidget::PortInfoAreaWidget(Session* session, int page_idx, QWidget *parent)
  : QScrollArea(parent), session_(session), page_idx_ {page_idx}
{
  QWidget *widget = new QWidget();
  this->setWidget( widget );
  //this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
  this->setWidgetResizable( true );

  main_layout_ = new QVBoxLayout();
  widget->setLayout(main_layout_);
}

void PortInfoAreaWidget::AddPort(int port_idx) {
  PortInfoWidget* port_info = new PortInfoWidget(session_, page_idx_, port_idx, this);
  port_info_widget_list_.append(port_info);
  main_layout_->addWidget(port_info);

  // Prevent from last widget deletion
  if(port_info_widget_list_.size() == 1) {
    port_info_widget_list_.at(0)->SetLastInList(true);
  } else {
    foreach (PortInfoWidget* port_info, port_info_widget_list_) {
      port_info->SetLastInList(false);
    }
  }
}

void PortInfoAreaWidget::DeletePort(int port_idx) {
  PortInfoWidget* port_info = port_info_widget_list_.at(port_idx);
  port_info_widget_list_.removeAt(port_idx);
  main_layout_->removeWidget(port_info);
  delete port_info;

  int index = 0;
  foreach (PortInfoWidget* port_info, port_info_widget_list_) {
    port_info->SetPortIndex(index);
    index++;
  }

  // Prevent from last widget deletion
  if(port_info_widget_list_.size() == 1) {
    port_info_widget_list_.at(0)->SetLastInList(true);
  }
}
