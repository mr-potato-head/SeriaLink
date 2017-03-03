#include "modepage.h"

ModePage::ModePage(ComPortManager* port_mgr, QWidget *parent)
  : QWidget(parent),
    port_manager_{port_mgr}
{
  main_layout_ = new QGridLayout(this);
  progress_bar_ = new QProgressBar(this);
  progress_bar_->setAlignment(Qt::AlignCenter);
  progress_bar_->setRange(0, 100);
  progress_label_ = new QLabel(tr("--"));
  progress_label_->setAlignment(Qt::AlignCenter);
  progress_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  send_button_ = new QPushButton(tr("Send !"));
  send_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  progress_bar_layout_ = new QHBoxLayout();
  progress_bar_layout_->addWidget(progress_bar_);
  progress_bar_layout_->addWidget(progress_label_);
  progress_bar_layout_->setStretch(0, 80);
  progress_bar_layout_->setStretch(1, 20);
  main_layout_->addWidget(send_button_, 0, 2, 2, 1);
  main_layout_->setColumnStretch(0, 80);
  main_layout_->setColumnStretch(1, 10);
  main_layout_->setColumnStretch(2, 10);

  // Signals connection
  connect(this, &ModePage::StartManualSequence,
          port_manager_, &ComPortManager::OnStartManualSequence);
  connect(this, &ModePage::StartDumpSequence,
          port_manager_, &ComPortManager::OnStartDumpSequence);
  connect(this, &ModePage::StartAutoSequence,
          port_manager_, &ComPortManager::OnStartAutoSequence);
  connect(this, &ModePage::StopSequence,
          port_manager_, &ComPortManager::OnStopSequence);
  connect(port_manager_, &ComPortManager::SequenceProgress,
          progress_bar_, &QProgressBar::setValue);
}

ModePage::~ModePage()
{
}
