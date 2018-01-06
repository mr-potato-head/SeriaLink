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

#include "src/manualmodepage.h"
#include "src/dataparser.h"

ManualModePage::ManualModePage(QWidget *parent)
  : ModePage(parent) {
  data_line_ = new QLineEdit(this);
  data_line_->setPlaceholderText(tr("Enter data here..."));
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
  frames_label_ = new QLabel(tr("frames"), this);
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

  main_layout_->addWidget(data_line_, 0, 0);
  main_layout_->addWidget(loop_groupbox_, 1, 0);
  main_layout_->addWidget(parser_groupbox_, 0, 1, 2, 1);

  // Radio button connections
  connect(ascii_radio_, &QRadioButton::toggled, [=](bool state) {
    if (state) {
      parser_type_ = DataParser::ParserType::kAscii;
      UpdateButtonEnabledState();
    }
  });
  connect(hex_radio_, &QRadioButton::toggled, [=](bool state) {
    if (state) {
      parser_type_ = DataParser::ParserType::kHex;
      UpdateButtonEnabledState();
    }
  });
  connect(dec_radio_, &QRadioButton::toggled, [=](bool state) {
    if (state) {
      parser_type_ = DataParser::ParserType::kDec;
      UpdateButtonEnabledState();
    }
  });

  // Button connection
  connect(start_button_, &QPushButton::clicked,
          this, &ManualModePage::OnStartButtonClicked);
  connect(data_line_, &QLineEdit::textChanged, [=](void) {
    UpdateButtonEnabledState();
  });
}

void ManualModePage::OnStartButtonClicked(void) {
  emit StartManualSequence(parser_type_, data_line_->text(),
                           repeat_spinbox_->value(),
                           delay_spinbox_->value());
}

void ManualModePage::UpdateButtonEnabledState(void) {
  if (data_line_->text().isEmpty()) {
    start_button_->setEnabled(false);
  } else {
    if (DataParser::CheckString(parser_type_, data_line_->text())) {
      start_button_->setEnabled(true);
    } else {
      start_button_->setEnabled(false);
    }
  }
}
