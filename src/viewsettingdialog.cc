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

static const int kMinimumWidth = 400;

ViewSettingDialog::ViewSettingDialog(ViewSettings* view_settings,
                                     ActionType action_type,
                                     QWidget *parent)
  : QDialog(parent),
    view_settings_{view_settings} {
  view_type_label_ = new QLabel(tr("View type"), this);
  view_type_combobox_ = new QComboBox(this);
  display_type_label_ = new QLabel(tr("Display type"), this);
  display_type_combobox_ = new QComboBox(this);
  data_size_label_ = new QLabel(tr("Data size"), this);
  data_size_combobox_ = new QComboBox(this);
  block_timeout_label_ = new QLabel(tr("Packet timeout (ms)"), this);
  block_timeout_spinbox_ = new QSpinBox(this);
  block_timeout_spinbox_->setMinimum(0);
  block_timeout_spinbox_->setMaximum(INT32_MAX);
  block_size_label_ = new QLabel(tr("Packet size"), this);
  block_size_spinbox_ = new QSpinBox(this);
  block_size_spinbox_->setMinimum(0);
  block_size_spinbox_->setMaximum(INT32_MAX);

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

  int row_index = 0;
  form_grid_layout_ = new QGridLayout(this);
  form_grid_layout_->addWidget(view_type_label_, row_index, 0);
  form_grid_layout_->addWidget(view_type_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(display_type_label_, row_index, 0);
  form_grid_layout_->addWidget(display_type_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(data_size_label_, row_index, 0);
  form_grid_layout_->addWidget(data_size_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(block_timeout_label_, row_index, 0);
  form_grid_layout_->addWidget(block_timeout_spinbox_, row_index++, 1);
  form_grid_layout_->addWidget(block_size_label_, row_index, 0);
  form_grid_layout_->addWidget(block_size_spinbox_, row_index++, 1);
  form_grid_layout_->addWidget(button_bar_, row_index, 0, 1, 2);

  // Fill comboboxes
  FillViewTypeList();
  FillDisplayTypeList();
  FillDataSizeList();

  // Special process if add or update view
  if (action_type == ActionType::kAdd) {
    this->setWindowTitle(tr("Choose view settings"));
  } else if (action_type == ActionType::kUpdate) {
    this->setWindowTitle(tr("Update view settings"));

    // Preset old settings
    int index = 0;

    int view_value = static_cast<qint32>(view_settings->GetViewType());
    index = view_type_combobox_->findData(view_value);
    view_type_combobox_->setCurrentIndex(index);

    int display_value = static_cast<qint32>(view_settings->GetDisplayType());
    index = display_type_combobox_->findData(display_value);
    display_type_combobox_->setCurrentIndex(index);

    int datasize = static_cast<qint32>(view_settings->GetDataSize());
    index = data_size_combobox_->findData(datasize);
    data_size_combobox_->setCurrentIndex(index);

    block_timeout_spinbox_->setValue(view_settings->GetDataBlockTimeout());
    block_size_spinbox_->setValue(view_settings->GetDataBlockSize());

    view_type_combobox_->setEnabled(false);
  } else {
    // Should not happened
    this->setWindowTitle(tr("View settings"));
  }

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
