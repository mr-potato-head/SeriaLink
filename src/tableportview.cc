#include <QHeaderView>
#include "src/tableportview.h"
#include "src/dataformatter.h"

TablePortView::TablePortView(ViewSettings* view_settings, QWidget* parent)
  : PortView{view_settings, parent} {
  table_widget_ = new QTableWidget(this);
  table_widget_->setColumnCount(2);
  table_widget_->setHorizontalHeaderLabels({tr("Datetime"), tr("Data")});
  QHeaderView *headerView = table_widget_->horizontalHeader();
  headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  headerView->setSectionResizeMode(1, QHeaderView::Interactive);
  headerView->setStretchLastSection(true);
  main_layout_->addWidget(table_widget_, 1, 0);

  // Signal connections
  connect(clear_button_, &QPushButton::clicked, [=](void) {
    table_widget_->clear();
    current_row_idx_ = 0;
  });
}

void TablePortView::OnReceivedData(const DataPacket& packet) {
  table_widget_->insertRow(current_row_idx_);

  QString dt = packet.GetDateTime().toString("dd/MM/yy - hh:mm:ss");
  QTableWidgetItem *dtItem = new QTableWidgetItem(dt);
  table_widget_->setItem(current_row_idx_, 0, dtItem);

  QString str = DataFormatter::formatData(*view_settings_, packet);
  QTableWidgetItem *strItem = new QTableWidgetItem(str);
  table_widget_->setItem(current_row_idx_, 1, strItem);

  if(capture_in_progress_) {
    *capture_stream_ << dt << ";" << str << "\r";
  }
  current_row_idx_++;
}
