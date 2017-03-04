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
  progress_label_->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  button_layout_ = new QVBoxLayout();
  start_button_ = new QPushButton(tr("Send !"));
  start_button_->setSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Expanding);
  stop_button_ = new QPushButton(tr("Stop"));
  stop_button_->setSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Expanding);
  stop_button_->setEnabled(false);
  button_layout_->addWidget(start_button_);
  button_layout_->addWidget(stop_button_);
  button_layout_->setStretch(0, 60);
  button_layout_->setStretch(1, 40);
  progress_bar_layout_ = new QHBoxLayout();
  progress_bar_layout_->addWidget(progress_bar_);
  progress_bar_layout_->addWidget(progress_label_);
  progress_bar_layout_->setStretch(0, 80);
  progress_bar_layout_->setStretch(1, 20);
  main_layout_->addLayout(button_layout_, 0, 2, 2, 1);
  main_layout_->setColumnStretch(0, 80);
  main_layout_->setColumnStretch(1, 10);
  main_layout_->setColumnStretch(2, 10);

  // Signals connection
  connect(this, &ModePage::StartDumpSequence,
          port_manager_, &ComPortManager::OnStartDumpSequence);
  connect(this, &ModePage::StartAutoSequence,
          port_manager_, &ComPortManager::OnStartAutoSequence);
  connect(port_manager_, &ComPortManager::SequenceProgress,
          progress_bar_, &QProgressBar::setValue);
  connect(this, &ModePage::StartManualSequence,
          port_manager_, &ComPortManager::OnStartManualSequence);
  connect(start_button_, &QPushButton::clicked,
          this, [=](void) {
    start_button_->setEnabled(false);
    stop_button_->setEnabled(true);
  });
  connect(stop_button_, &QPushButton::clicked,
          port_manager_, &ComPortManager::OnStopSequence);
  connect(stop_button_, &QPushButton::clicked,
          this, [=](void) {
    progress_bar_->setValue(0);
    start_button_->setEnabled(true);
    stop_button_->setEnabled(false);
  });
  connect(port_manager_, &ComPortManager::SequenceOver,
          this, [=](void) {
    start_button_->setEnabled(true);
    stop_button_->setEnabled(false);
  });
}

ModePage::~ModePage()
{
}
