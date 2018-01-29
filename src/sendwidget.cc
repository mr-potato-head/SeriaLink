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

#include "src/sendwidget.h"

SendWidget::SendWidget(QList<ComPortManager*>* port_mgr_list,
                       QWidget *parent)
  : QWidget(parent),
    port_mgr_list_ {port_mgr_list} {
  mode_label_ = new QLabel(tr("Mode"), this);
  mode_label_->setAlignment(Qt::AlignCenter);
  mode_combobox_ = new QComboBox(this);
  mode_combobox_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mode_combobox_->addItem(tr("Manual"), static_cast<int>(MODES::MANUAL));
  mode_combobox_->addItem(tr("Dump"), static_cast<int>(MODES::DUMP));
  //  mode_combobox_->addItem(tr("Auto"), static_cast<int>(MODES::AUTO));
  stacked_widget_ = new QStackedWidget(this);

  manual_mode_page_ = new ManualModePage(port_mgr_list_, this);
  stacked_widget_->addWidget(manual_mode_page_);
  dump_mode_page_ = new DumpModePage(port_mgr_list_, this);
  stacked_widget_->addWidget(dump_mode_page_);

  port_label_ = new QLabel(tr("Port"), this);
  port_label_->setAlignment(Qt::AlignCenter);

  port_combobox_ = new QComboBox(this);
  port_combobox_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  connect(port_combobox_, SIGNAL(currentIndexChanged(int)),
          manual_mode_page_, SLOT(ChangePortManagerIndex(int)));

  foreach (ComPortManager* port_mgr, *port_mgr_list) { // NOLINT
    ComPortSettings* port_settings = port_mgr->GetPortSettings();
    port_combobox_->addItem(port_settings->GetPortInfo().portName());
  }

  mode_layout_ = new QVBoxLayout();
  mode_layout_->addWidget(mode_label_);
  mode_layout_->addWidget(mode_combobox_);
  mode_layout_->addWidget(port_label_);
  mode_layout_->addWidget(port_combobox_);
  mode_layout_->setStretch(0, 25);
  mode_layout_->setStretch(1, 25);
  mode_layout_->setStretch(2, 25);
  mode_layout_->setStretch(3, 25);

  main_layout_ = new QGridLayout(this);
  main_layout_->addLayout(mode_layout_, 0, 0);
  main_layout_->addWidget(stacked_widget_, 0, 1);

  // Connexion des signaux
  connect(mode_combobox_, SIGNAL(currentIndexChanged(int)),
          stacked_widget_, SLOT(setCurrentIndex(int)));
}

void SendWidget::PortListUpdated(void) {
  port_combobox_->clear();
  QList<ComPortManager*>::iterator itBeginTh = (*port_mgr_list_).begin();
  QList<ComPortManager*>::iterator itEndTh = (*port_mgr_list_).end();
  for (QList<ComPortManager*>::iterator it = itBeginTh ; it != itEndTh ; it++) {
    ComPortSettings* settings = (*it)->GetPortSettings();
    port_combobox_->addItem(settings->GetPortInfo().portName());
  }
}
