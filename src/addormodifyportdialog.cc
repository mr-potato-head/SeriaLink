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

#include "src/addormodifyportdialog.h"
#include <QtSerialPort/QtSerialPort>

static const char kBlankString[] =
    QT_TRANSLATE_NOOP("AddOrModifyPortDialog", "N/A");

static const quint16 kMinimumWidth = 400;
static const quint8 kPortComboBoxSF = 85;
static const quint8 kPortUpdateBtnSF = 15;

AddOrModifyPortDialog::AddOrModifyPortDialog(ComPortSettings* port_settings,
                                             ActionType action_type,
                                             QWidget *parent)
  : QDialog(parent),
    port_settings_{port_settings} {
  this->setWindowTitle(tr("Port settings"));
  port_label_ = new QLabel(tr("Port"), this);
  port_combobox_ = new QComboBox(this);
  port_list_upd_button_ = new QPushButton(this);
  port_list_upd_button_->setIcon(QIcon(":/icons/icons/loop-circular-8x.png"));
  port_list_upd_button_->setToolTip(tr("Update port list."));
  baud_rate_label_ = new QLabel(tr("Baud rate"), this);
  baudrate_combobox_ = new QComboBox(this);
  parity_label_ = new QLabel(tr("Parity"), this);
  parity_combobox_ = new QComboBox(this);
  data_bits_label_ = new QLabel(tr("Data bits"), this);
  data_bits_combobox_ = new QComboBox(this);
  stop_bits_label_ = new QLabel(tr("Stop bits"), this);
  stop_bits_combobox_ = new QComboBox(this);
  flow_control_label_ = new QLabel(tr("Flow control"), this);
  flow_control_combobox_ = new QComboBox(this);

  port_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding);
  port_list_upd_button_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
  baudrate_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);
  parity_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Expanding);
  data_bits_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);
  stop_bits_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Expanding);
  flow_control_combobox_->setSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Expanding);

  button_bar_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                     QDialogButtonBox::Cancel);

  connect(button_bar_, SIGNAL(accepted()), this, SLOT(FillPortSettings()));
  connect(button_bar_, SIGNAL(rejected()), this, SLOT(reject()));

  port_hbox_layout_ = new QHBoxLayout();
  port_hbox_layout_->addWidget(port_combobox_);
  port_hbox_layout_->addWidget(port_list_upd_button_);

  port_hbox_layout_->setStretchFactor(
        static_cast<QWidget*>(port_combobox_), kPortComboBoxSF);
  port_hbox_layout_->setStretchFactor(
        static_cast<QWidget*>(port_list_upd_button_), kPortUpdateBtnSF);

  quint8 row_index = 0;
  form_grid_layout_ = new QGridLayout(this);
  form_grid_layout_->addWidget(port_label_, row_index, 0);
  form_grid_layout_->addLayout(port_hbox_layout_, row_index++, 1);
  form_grid_layout_->addWidget(baud_rate_label_, row_index, 0);
  form_grid_layout_->addWidget(baudrate_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(parity_label_, row_index, 0);
  form_grid_layout_->addWidget(parity_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(data_bits_label_, row_index, 0);
  form_grid_layout_->addWidget(data_bits_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(stop_bits_label_, row_index, 0);
  form_grid_layout_->addWidget(stop_bits_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(flow_control_label_, row_index, 0);
  form_grid_layout_->addWidget(flow_control_combobox_, row_index++, 1);
  form_grid_layout_->addWidget(button_bar_, row_index, 0, 1, 2);

  // Fill comboboxes
  FillPortList();
  FillBaudRateList();
  FillParityList();
  FillDataBitsList();
  FillStopBitsList();
  FillFlowControlList();

  // Special process if add or update port settings
  if(action_type == ActionType::kAdd) {
    this->setWindowTitle(tr("Choose port settings"));
  } else if(action_type == ActionType::kUpdate) {
    this->setWindowTitle(tr("Update port settings"));

    // Preset old settings
    int index = 0;
    port_combobox_->setCurrentText(port_settings->GetPortInfo().portName());
    index = baudrate_combobox_->findData(static_cast<qint32>(port_settings->GetBaudRate()));
    baudrate_combobox_->setCurrentIndex(index);
    index = parity_combobox_->findData(static_cast<qint32>(port_settings->GetParity()));
    parity_combobox_->setCurrentIndex(index);
    index = data_bits_combobox_->findData(static_cast<qint32>(port_settings->GetDataBits()));
    data_bits_combobox_->setCurrentIndex(index);
    index = stop_bits_combobox_->findData(static_cast<qint32>(port_settings->GetStopBits()));
    stop_bits_combobox_->setCurrentIndex(index);
    index = flow_control_combobox_->findData(static_cast<qint32>(port_settings->GetFlowControl()));
    flow_control_combobox_->setCurrentIndex(index);

  } else {
    // Should not happened
    this->setWindowTitle(tr("Port settings"));
  }

  // Dialog minimum width
  this->setMinimumWidth(kMinimumWidth);

  // Connect refresh button
  connect(port_list_upd_button_, SIGNAL(clicked()),
          this, SLOT(FillPortList()));
}

void AddOrModifyPortDialog::FillPortList(void) {
  // Clear current list
  port_combobox_->clear();

  // Fill with new data
  QString description;
  QString manufacturer;
  QString serial_number;
  foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    QStringList port_list;
    description = info.description();
    manufacturer = info.manufacturer();
    serial_number = info.serialNumber();
    port_list << info.portName()
              << (!description.isEmpty() ? description : kBlankString)
              << (!manufacturer.isEmpty() ? manufacturer : kBlankString)
              << (!serial_number.isEmpty() ? serial_number : kBlankString)
              << info.systemLocation()
              << (info.vendorIdentifier() ?
                    QString::number(info.vendorIdentifier(), 16) :
                    kBlankString)
              << (info.productIdentifier() ?
                    QString::number(info.productIdentifier(), 16) :
                    kBlankString);

    port_combobox_->addItem(port_list.first(), port_list);
  }
}

void AddOrModifyPortDialog::FillParityList(void) {
  parity_combobox_->addItem(tr("None"), QSerialPort::NoParity);
  parity_combobox_->addItem(tr("Even"), QSerialPort::EvenParity);
  parity_combobox_->addItem(tr("Odd"), QSerialPort::OddParity);
  parity_combobox_->addItem(tr("Mark"), QSerialPort::MarkParity);
  parity_combobox_->addItem(tr("Space"), QSerialPort::SpaceParity);
}

void AddOrModifyPortDialog::FillBaudRateList(void) {
  baudrate_combobox_->addItem(QStringLiteral("9600"),
                              QSerialPort::Baud9600);
  baudrate_combobox_->addItem(QStringLiteral("19200"),
                              QSerialPort::Baud19200);
  baudrate_combobox_->addItem(QStringLiteral("38400"),
                              QSerialPort::Baud38400);
  baudrate_combobox_->addItem(QStringLiteral("115200"),
                              QSerialPort::Baud115200);
}

void AddOrModifyPortDialog::FillDataBitsList(void) {
  data_bits_combobox_->addItem(QStringLiteral("5"), QSerialPort::Data5);
  data_bits_combobox_->addItem(QStringLiteral("6"), QSerialPort::Data6);
  data_bits_combobox_->addItem(QStringLiteral("7"), QSerialPort::Data7);
  data_bits_combobox_->addItem(QStringLiteral("8"), QSerialPort::Data8);
  data_bits_combobox_->setCurrentIndex(3);
}

void AddOrModifyPortDialog::FillStopBitsList(void) {
  stop_bits_combobox_->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
  stop_bits_combobox_->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
  stop_bits_combobox_->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

void AddOrModifyPortDialog::FillFlowControlList(void) {
  flow_control_combobox_->addItem(tr("None"), QSerialPort::NoFlowControl);
  flow_control_combobox_->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
  flow_control_combobox_->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void AddOrModifyPortDialog::FillPortSettings(void) {
  port_settings_->SetBaudRate(
        static_cast<QSerialPort::BaudRate>(
          baudrate_combobox_->itemData(
            baudrate_combobox_->currentIndex()).toInt()));
  port_settings_->SetParity(
        static_cast<QSerialPort::Parity>(
          parity_combobox_->itemData(
            parity_combobox_->currentIndex()).toInt()));
  port_settings_->SetStopBits(
        static_cast<QSerialPort::StopBits>(
          stop_bits_combobox_->itemData(
            stop_bits_combobox_->currentIndex()).toInt()));
  port_settings_->SetDataBits(
        static_cast<QSerialPort::DataBits>(
          data_bits_combobox_->itemData(
            data_bits_combobox_->currentIndex()).toInt()));
  port_settings_->SetFlowControl(
        static_cast<QSerialPort::FlowControl>(
          flow_control_combobox_->itemData(
            flow_control_combobox_->currentIndex()).toInt()));

  foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    if (info.portName() == port_combobox_->currentText()) {
      QSerialPortInfo port_info(info);
      port_settings_->SetPortInfo(port_info);
    }
  }

  this->accept();
}
