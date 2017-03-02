#include "manualmodepage.h"

ManualModePage::ManualModePage(ComPortManager* port_mgr, QWidget *parent)
  : ModePage(port_mgr, parent)
{
  manual_data_line_ = new QLineEdit(this);
  manual_data_line_->setPlaceholderText(tr("Enter data here..."));
  manual_loop_groupbox_ = new QGroupBox(tr("Loop"), this);
  manual_parser_groupbox_ = new QGroupBox(tr("Parser"), this);
  ascii_radio_ = new QRadioButton(tr("Ascii"), this);
  ascii_radio_->setChecked(true);
  hex_radio_ = new QRadioButton(tr("Hex"), this);
  dec_radio_ = new QRadioButton(tr("Dec"), this);
  parser_layout_ = new QVBoxLayout(manual_parser_groupbox_);
  parser_layout_->addWidget(ascii_radio_);
  parser_layout_->addWidget(hex_radio_);
  parser_layout_->addWidget(dec_radio_);
  loop_layout_ = new QGridLayout(manual_loop_groupbox_);

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
  repeat_spinbox_ = new QSpinBox(this);
  repeat_spinbox_->setMinimum(1);
  repeat_spinbox_->setAlignment(Qt::AlignCenter);

  loop_layout_->addWidget(repeat_label_, 0, 0);
  loop_layout_->addWidget(repeat_spinbox_, 0, 1);
  loop_layout_->addWidget(frames_label_, 0, 2);
  loop_layout_->addWidget(vertical_line_, 0, 3);
  loop_layout_->addWidget(delay_label_, 0, 4);
  loop_layout_->addWidget(delay_spinbox_, 0, 5);
  loop_layout_->addWidget(ms_label_, 0, 6);
  loop_layout_->addLayout(progress_bar_layout_, 1, 0, 1, 7);

  main_layout_->addWidget(manual_data_line_, 0, 0);
  main_layout_->addWidget(manual_loop_groupbox_, 1, 0);
  main_layout_->addWidget(manual_parser_groupbox_, 0, 1, 2, 1);
}
