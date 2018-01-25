#include "portinfoareawidget.h"

PortInfoAreaWidget::PortInfoAreaWidget(Session* session, quint8 page_idx, QWidget *parent)
  : QScrollArea(parent), session_(session), page_idx_ {page_idx}
{
  main_layout_ = new QVBoxLayout(this);
}

void PortInfoAreaWidget::AddPort(quint8 port_idx) {
  PortInfoWidget* port_info = new PortInfoWidget(session_, page_idx_, port_idx, this);
  port_info_widget_list_.append(port_info);
  main_layout_->addWidget(port_info);
}

void PortInfoAreaWidget::DeletePort(quint8 port_idx) {
  PortInfoWidget* port_info = port_info_widget_list_.at(port_idx);
  port_info_widget_list_.removeAt(port_idx);
  main_layout_->removeWidget(port_info);
  delete port_info;

  // TODO mettre à jour les index des autres port_info restants
}
