#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent)
{
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

  about_button_ = new QPushButton(this);
  about_button_->setIcon(QIcon(":/icons/icons/question-mark-8x.png"));
  about_button_->setFixedSize(60, 60);

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(about_button_);
}

void MenuWidget::focusOutEvent(QFocusEvent *)
{
    close();
}
