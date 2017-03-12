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

#include "src/viewsettingdialog.h"

static const quint16 kMinimumWidth = 400;

ViewSettingDialog::ViewSettingDialog(ViewSettings* view_settings,
                                     QWidget *parent)
  : QDialog(parent),
    view_settings_{view_settings} {
  this->setWindowTitle(tr("View settings"));

  view_type_label_ = new QLabel(tr("View type"), this);
  view_type_combobox_ = new QComboBox(this);
  display_type_label_ = new QLabel(tr("Display type"), this);
  display_type_combobox_ = new QComboBox(this);
  data_size_label_ = new QLabel(tr("Data size"), this);
  data_size_combobox_ = new QComboBox(this);

  view_type_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);
  display_type_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Expanding);
  data_size_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);

  button_bar_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                     QDialogButtonBox::Cancel);

  connect(button_bar_, SIGNAL(accepted()), this, SLOT(FillViewSettings()));
  connect(button_bar_, SIGNAL(rejected()), this, SLOT(reject()));

  quint8 row_index = 0;
  form_grid_layout_ = new QGridLayout(this);
  form_grid_layout_->addWidget(view_type_label_, row_index, 0);
  form_grid_layout_->addWidget(view_type_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(display_type_label_, row_index, 0);
  form_grid_layout_->addWidget(display_type_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(data_size_label_, row_index, 0);
  form_grid_layout_->addWidget(data_size_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(button_bar_, row_index, 0, 1, 2);

  // Fill comboboxes
  FillViewTypeList();
  FillDisplayTypeList();
  FillDataSizeList();

  // Dialog minimum width
  this->setMinimumWidth(kMinimumWidth);
}

void ViewSettingDialog::FillViewSettings(void) {
  view_settings_->SetViewType(
        static_cast<ViewSettings::ViewType>(
          view_type_combobox_->itemData(
            view_type_combobox_->currentIndex()).toInt()));
  view_settings_->SetDisplayType(
        static_cast<ViewSettings::DisplayType>(
          display_type_combobox_->itemData(
            display_type_combobox_->currentIndex()).toInt()));
  view_settings_->SetDataSize(
        static_cast<ViewSettings::DataSize>(
          data_size_combobox_->itemData(
            data_size_combobox_->currentIndex()).toInt()));
  this->accept();
}

void ViewSettingDialog::FillViewTypeList(void) {
  view_type_combobox_->addItem(QStringLiteral("Terminal"),
                               (qint32)ViewSettings::ViewType::kTerminal);
  view_type_combobox_->addItem(QStringLiteral("Dump"),
                               (qint32)ViewSettings::ViewType::kDump);
  view_type_combobox_->addItem(QStringLiteral("Table"),
                               (qint32)ViewSettings::ViewType::kTable);
  view_type_combobox_->setCurrentIndex(0);
}

void ViewSettingDialog::FillDisplayTypeList(void) {
  display_type_combobox_->addItem(QStringLiteral("Ascii"),
                                  (qint32)ViewSettings::DisplayType::kAscii);
  display_type_combobox_->addItem(QStringLiteral("Hex"),
                                  (qint32)ViewSettings::DisplayType::kHexa);
  display_type_combobox_->addItem(QStringLiteral("Dec"),
                                  (qint32)ViewSettings::DisplayType::kDec);
  display_type_combobox_->setCurrentIndex(0);
}

void ViewSettingDialog::FillDataSizeList(void) {
  data_size_combobox_->addItem(QStringLiteral("No size"),
                               (qint32)ViewSettings::DataSize::kNoSize);
  data_size_combobox_->addItem(QStringLiteral("1 Byte"),
                               (qint32)ViewSettings::DataSize::k1Byte);
  data_size_combobox_->addItem(QStringLiteral("2 Bytes"),
                               (qint32)ViewSettings::DataSize::k2Bytes);
  data_size_combobox_->addItem(QStringLiteral("4 Bytes"),
                               (qint32)ViewSettings::DataSize::k4Bytes);
  data_size_combobox_->addItem(QStringLiteral("8 Bytes"),
                               (qint32)ViewSettings::DataSize::k8Bytes);
  data_size_combobox_->setCurrentIndex(0);
}
