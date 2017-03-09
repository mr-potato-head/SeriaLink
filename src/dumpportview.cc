#include "src/dumpportview.h"
#include "src/dataformatter.h"

DumpPortView::DumpPortView(ViewSettings* view_settings, QWidget* parent)
  : PortView{view_settings, parent} {
  text_edit_ = new QPlainTextEdit(this);
  main_layout_->addWidget(text_edit_, 1, 0);

  // Signal connections
  connect(clear_button_, &QPushButton::clicked, [=](void) {
    text_edit_->clear();
  });
}

void DumpPortView::OnReceivedData(const DataPacket& packet) {
  QString str = packet.GetDateTime().toString("dd.MM.yyyy at hh:mm:ss.zzz");
  str += "\r  ";
  str += DataFormatter::formatData(*view_settings_, packet);
  text_edit_->appendPlainText(str);
  if(capture_in_progress_) {
    *capture_stream_ << str;
  }
}
