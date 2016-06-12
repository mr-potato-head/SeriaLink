#include "portview.h"

PortView::PortView(QWidget *parent)
  : QWidget(parent) {
  main_layout_ = new QGridLayout(this);
  text_edit_ = new QTextEdit(this);

  main_layout_->addWidget(text_edit_);
}

void PortView::OnReceivedData(QByteArray data) {
    text_edit_->append(QString(data));
}
