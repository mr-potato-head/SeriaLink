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
#include <QDesktopServices>
#include <QMessageBox>
#include "src/portview.h"
#include "src/dataformatter.h"
#include "src/viewsettingdialog.h"

PortView::PortView(ViewSettings* view_settings,
                   QWidget *parent)
  : QWidget(parent),
    view_settings_{view_settings} {
  capture_in_progress_ = false;
  button_layout_ = new QHBoxLayout();
  spacer_item_ = new QSpacerItem(0, 0, QSizePolicy::Expanding);
  button_layout_->addSpacerItem(spacer_item_);
  delete_button_ = new QPushButton(this);
  delete_button_->setIcon(QIcon(":/icons/icons/circle-x-8x.png"));
  delete_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  delete_button_->setToolTip(tr("Delete view."));
  edit_button_ = new QPushButton(this);
  edit_button_->setIcon(QIcon(":/icons/icons/pencil-8x.png"));
  edit_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  edit_button_->setToolTip(tr("Edit view settings."));
  clear_button_ = new QPushButton(this);
  clear_button_->setIcon(QIcon(":/icons/icons/trash-8x.png"));
  clear_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  clear_button_->setToolTip(tr("Clear view."));
  button_layout_->addWidget(clear_button_);
  button_layout_->addWidget(edit_button_);
  button_layout_->addWidget(delete_button_);
  button_layout_->setStretch(0, 70);
  button_layout_->setStretch(1, 10);
  button_layout_->setStretch(2, 10);
  button_layout_->setStretch(3, 10);

  capture_groupbox_ = new QGroupBox(tr("Capture"), this);
  capture_layout_ = new QGridLayout(capture_groupbox_);
  cap_spacer_item_ = new QSpacerItem(0, 0,
                                     QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);
  open_button_ = new QPushButton(this);
  open_button_->setIcon(QIcon(":/icons/icons/external-link-8x.png"));
  browse_button_ = new QPushButton(this);
  browse_button_->setIcon(QIcon(":/icons/icons/magnifying-glass-8x.png"));
  start_rec_button_ = new QPushButton(this);
  start_rec_button_->setIcon(QIcon(":/icons/icons/media-record-8x.png"));
  start_rec_button_->setEnabled(false);
  stop_rec_button_ = new QPushButton(this);
  stop_rec_button_->setIcon(QIcon(":/icons/icons/media-stop-8x.png"));
  stop_rec_button_->setEnabled(false);
  overwrite_button_ = new QRadioButton(tr("Overwrite"), this);
  overwrite_button_->setChecked(true);
  append_button_ = new QRadioButton(tr("Append"), this);
  file_mode_layout_ = new QHBoxLayout();
  file_mode_layout_->addWidget(overwrite_button_);
  file_mode_layout_->addWidget(append_button_);
  file_mode_layout_->addSpacerItem(cap_spacer_item_);
  file_path_ = new QLineEdit(this);
  file_path_->setPlaceholderText(tr("Enter file path here..."));

  capture_layout_->addWidget(file_path_, 0, 0);
  capture_layout_->addLayout(file_mode_layout_, 1, 0);
  capture_layout_->addWidget(browse_button_, 0, 1);
  capture_layout_->addWidget(open_button_, 0, 2);
  capture_layout_->addWidget(start_rec_button_, 1, 1);
  capture_layout_->addWidget(stop_rec_button_, 1, 2);

  main_layout_ = new QGridLayout(this);
  main_layout_->addLayout(button_layout_, 0, 0);
  main_layout_->addWidget(capture_groupbox_, 2, 0);
  main_layout_->setRowStretch(0, 5);
  main_layout_->setRowStretch(1, 75);
  main_layout_->setRowStretch(2, 20);

  connect(delete_button_, &QPushButton::clicked, [=](void) {
    emit DeleteView(this);
  });
  connect(browse_button_, &QPushButton::clicked, [=](void) {
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Choose capture file"),
                                     ".", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()) {
      file_path_->setText(fileName);
      start_rec_button_->setEnabled(true);
      stop_rec_button_->setEnabled(false);
    }
  });

  connect(open_button_, &QPushButton::clicked, [=](void) {
    QDesktopServices::openUrl(QUrl("file:" + file_path_->text()));
  });

  connect(start_rec_button_, &QPushButton::clicked, [=](void) {
    capture_file_ = new QFile(file_path_->text());
    if (!capture_file_->open(QIODevice::WriteOnly | QIODevice::Text)) {
      QMessageBox::critical(this, tr("File error"),
                            tr("Can't open ") + file_path_->text());
    } else {
      capture_stream_ = new QTextStream(capture_file_);
      start_rec_button_->setEnabled(false);
      stop_rec_button_->setEnabled(true);
      capture_in_progress_ = true;
    }
  });

  connect(stop_rec_button_, &QPushButton::clicked, [=](void) {
    capture_file_->close();
    start_rec_button_->setEnabled(true);
    stop_rec_button_->setEnabled(false);
    capture_in_progress_ = false;
  });

  connect(file_path_, &QLineEdit::textChanged, [=](void) {
    if (!file_path_->text().isEmpty()) {
      start_rec_button_->setEnabled(true);
    } else {
      start_rec_button_->setEnabled(false);
    }
  });

  connect(edit_button_, &QPushButton::clicked, [=](void) {
    ViewSettingDialog view_setting_dialog(view_settings_,
                                          ViewSettingDialog::ActionType::kUpdate,
                                          this);
    view_setting_dialog.exec();
  });
}

PortView::~PortView(void) {
  delete capture_file_;
  delete view_settings_;
}

ViewSettings* PortView::GetViewSettings(void) {
  return view_settings_;
}
