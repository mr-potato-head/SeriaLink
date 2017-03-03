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

SendWidget::SendWidget(SessionManager* session_manager,
                       qint32 port_index, QWidget *parent)
  : QWidget(parent),
    session_manager_{session_manager},
    port_index_{port_index} {
  mode_label_ = new QLabel(tr("Mode"), this);
  mode_label_->setAlignment(Qt::AlignCenter);
  mode_combobox_ = new QComboBox(this);
  mode_combobox_->addItem(tr("Manual"), (int)MODES::MANUAL);
  //mode_combobox_->addItem(tr("Dump"), (int)MODES::DUMP);
  //mode_combobox_->addItem(tr("Auto"), (int)MODES::AUTO);
  stacked_widget_ = new QStackedWidget(this);

  Session* session = session_manager_->GetCurrentSession();
  ComPortManager* port_mgr = session->GetPortManager(port_index_);
  manual_mode_page_ = new ManualModePage(port_mgr, this);
  stacked_widget_->addWidget(manual_mode_page_);

  mode_layout_ = new QVBoxLayout();
  mode_layout_->addWidget(mode_label_);
  mode_layout_->addWidget(mode_combobox_);
  mode_layout_->setStretch(0, 33);
  mode_layout_->setStretch(1, 33);
  mode_layout_->addStretch(33);

  main_layout_ = new QGridLayout(this);
  main_layout_->addLayout(mode_layout_, 0, 0);
  main_layout_->addWidget(stacked_widget_, 0, 1);
}
