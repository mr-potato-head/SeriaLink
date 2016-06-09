#include "portview.h"

PortView::PortView(QWidget *parent)
  : QWidget(parent) {
  main_layout_ = new QGridLayout(this);
  text_edit_ = new QTextEdit(this);

  main_layout_->addWidget(text_edit_);
}
