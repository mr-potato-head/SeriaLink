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

#include <QFileDialog>
#include "src/dumpmodepage.h"

DumpModePage::DumpModePage(QList<ComPortManager*>* port_mgr_list,
                           QWidget *parent)
  : ModePage(port_mgr_list, parent) {
  path_line_ = new QLineEdit(this);
  path_line_->setPlaceholderText(tr("Enter dump file path here..."));
  path_line_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  browse_button_ = new QPushButton(tr("Browse..."));
  path_layout_ = new QHBoxLayout();
  path_layout_->addWidget(path_line_);
  path_layout_->addWidget(browse_button_);
  path_layout_->setStretch(0, 80);
  path_layout_->setStretch(1, 20);
  loop_groupbox_ = new QGroupBox(tr("Loop"), this);
  parser_groupbox_ = new QGroupBox(tr("Parser"), this);
  ascii_radio_ = new QRadioButton(tr("Ascii"), this);
  ascii_radio_->setChecked(true);
  hex_radio_ = new QRadioButton(tr("Hex"), this);
  dec_radio_ = new QRadioButton(tr("Dec"), this);
  parser_layout_ = new QVBoxLayout(parser_groupbox_);
  parser_layout_->addWidget(ascii_radio_);
  parser_layout_->addWidget(hex_radio_);
  parser_layout_->addWidget(dec_radio_);
  loop_layout_ = new QGridLayout(loop_groupbox_);

  delay_label_ = new QLabel(tr("Delay"), this);
  delay_label_->setAlignment(Qt::AlignCenter);
  ms_label_ = new QLabel(tr("ms"), this);
  ms_label_->setAlignment(Qt::AlignCenter);

  vertical_line_ = new QWidget;
  vertical_line_->setFixedWidth(2);
  vertical_line_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  vertical_line_->setStyleSheet(QString("background-color: #c0c0c0;"));

  repeat_label_ = new QLabel(tr("Repeat"), this);
  repeat_label_->setAlignment(Qt::AlignCenter);
  frames_label_ = new QLabel(tr("times"), this);
  frames_label_->setAlignment(Qt::AlignCenter);

  delay_spinbox_ = new QSpinBox(this);
  delay_spinbox_->setAlignment(Qt::AlignCenter);
  delay_spinbox_->setRange(1, INT_MAX);
  repeat_spinbox_ = new QSpinBox(this);
  repeat_spinbox_->setRange(1, INT_MAX);
  repeat_spinbox_->setAlignment(Qt::AlignCenter);

  loop_layout_->addWidget(repeat_label_, 0, 0);
  loop_layout_->addWidget(repeat_spinbox_, 0, 1);
  loop_layout_->addWidget(frames_label_, 0, 2);
  loop_layout_->addWidget(vertical_line_, 0, 3);
  loop_layout_->addWidget(delay_label_, 0, 4);
  loop_layout_->addWidget(delay_spinbox_, 0, 5);
  loop_layout_->addWidget(ms_label_, 0, 6);
  loop_layout_->addLayout(progress_bar_layout_, 1, 0, 1, 7);

  main_layout_->addLayout(path_layout_, 0, 0);
  main_layout_->addWidget(loop_groupbox_, 1, 0);
  main_layout_->addWidget(parser_groupbox_, 0, 1, 2, 1);

  start_button_->setEnabled(false);
  stop_button_->setEnabled(false);

  // Button connection
  connect(start_button_, &QPushButton::clicked,
          this, &DumpModePage::OnStartButtonClicked);
  connect(browse_button_, &QPushButton::clicked, [=](void) {
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open data file"), ".", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()) {
      path_line_->setText(fileName);
      start_button_->setEnabled(true);
      stop_button_->setEnabled(false);
    }
  });
}

void DumpModePage::OnStartButtonClicked(void) {
  DataParser::ParserType eType = DataParser::ParserType::kUnknown;
  if (ascii_radio_->isChecked()) {
    eType = DataParser::ParserType::kAscii;
  } else if (hex_radio_->isChecked()) {
    eType = DataParser::ParserType::kHex;
  } else if (dec_radio_->isChecked()) {
    eType = DataParser::ParserType::kDec;
  } else {
    // Should not be here
    eType = DataParser::ParserType::kUnknown;
  }
  emit StartDumpSequence(eType, path_line_->text(),
                         repeat_spinbox_->value(),
                         delay_spinbox_->value());
}
