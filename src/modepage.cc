/*
 * Copyright (C) 2016 Guilhem GUYONNET
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "src/modepage.h"

ModePage::ModePage(QList<ComPortManager*>* port_mgr_list,
                   QWidget *parent)
  : QWidget(parent),
    port_mgr_list_ {port_mgr_list} {
  main_layout_ = new QGridLayout(this);
  progress_bar_ = new QProgressBar(this);
  progress_bar_->setAlignment(Qt::AlignCenter);
  progress_bar_->setRange(0, 100);
  progress_label_ = new QLabel(tr("--"));
  progress_label_->setAlignment(Qt::AlignCenter);
  progress_label_->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  button_layout_ = new QVBoxLayout();
  start_button_ = new QPushButton(tr("Start !"));
  start_button_->setSizePolicy(QSizePolicy::Expanding,
                               QSizePolicy::Expanding);
  stop_button_ = new QPushButton(tr("Stop"));
  stop_button_->setSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Expanding);
  start_button_->setEnabled(false);
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
  connect(start_button_, &QPushButton::clicked,
          this, [=](void) {
    start_button_->setEnabled(false);
    stop_button_->setEnabled(true);
  });
  connect(stop_button_, &QPushButton::clicked,
          this, [=](void) {
    progress_bar_->setValue(0);
    start_button_->setEnabled(true);
    stop_button_->setEnabled(false);
  });
}

ModePage::~ModePage() {}

void ModePage::ChangePortManagerIndex(int index) {

  if(port_manager_ != nullptr) {
    // Disconnect all signals from old port manager
    disconnect(this, &ModePage::StartDumpSequence,
               port_manager_, &ComPortManager::OnStartDumpSequence);
    disconnect(this, &ModePage::StartAutoSequence,
               port_manager_, &ComPortManager::OnStartAutoSequence);
    disconnect(this, &ModePage::StartManualSequence,
               port_manager_, &ComPortManager::OnStartManualSequence);
    disconnect(port_manager_, &ComPortManager::SequenceProgress,
               progress_bar_, &QProgressBar::setValue);
    disconnect(port_manager_, &ComPortManager::SequenceOver,
               this, ModePage::OnStopButtonClicked);
    disconnect(stop_button_, &QPushButton::clicked,
               port_manager_, &ComPortManager::OnStopSequence);
  }

  if(index >= 0) {
    // Set new port manager
    port_manager_ = port_mgr_list_->at(index);

    // Connect new port manager
    connect(this, &ModePage::StartDumpSequence,
            port_manager_, &ComPortManager::OnStartDumpSequence);
    connect(this, &ModePage::StartAutoSequence,
            port_manager_, &ComPortManager::OnStartAutoSequence);
    connect(this, &ModePage::StartManualSequence,
            port_manager_, &ComPortManager::OnStartManualSequence);
    connect(port_manager_, &ComPortManager::SequenceProgress,
            progress_bar_, &QProgressBar::setValue);
    connect(port_manager_, &ComPortManager::SequenceOver,
            this, ModePage::OnStopButtonClicked);
    connect(stop_button_, &QPushButton::clicked,
            port_manager_, &ComPortManager::OnStopSequence);
  }

  //  connect(this, &ModePage::StartDumpSequence,
  //          port_manager_, &ComPortManager::OnStartDumpSequence);
  //  connect(this, &ModePage::StartAutoSequence,
  //          port_manager_, &ComPortManager::OnStartAutoSequence);
  //  connect(this, &ModePage::StartManualSequence,
  //          port_manager_, &ComPortManager::OnStartManualSequence);
  //  connect(port_manager_, &ComPortManager::SequenceProgress,
  //          progress_bar_, &QProgressBar::setValue);
  //  connect(port_manager_, &ComPortManager::SequenceOver, this, [=](void) );
  //  connect(stop_button_, &QPushButton::clicked,
  //          port_manager_, &ComPortManager::OnStopSequence);
}

void ModePage::OnStopButtonClicked(void)
{
  start_button_->setEnabled(true);
  stop_button_->setEnabled(false);
}
