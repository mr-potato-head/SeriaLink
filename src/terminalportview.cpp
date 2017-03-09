#include "src/terminalportview.h"
#include "src/dataformatter.h"

TerminalPortView::TerminalPortView(ViewSettings* view_settings, QWidget* parent)
  : PortView{view_settings, parent}{
  text_edit_ = new QPlainTextEdit(this);
  main_layout_->addWidget(text_edit_, 1, 0);

  // Signal connections
  connect(clear_button_, &QPushButton::clicked, [=](void) {
    text_edit_->clear();
  });
}

void TerminalPortView::OnReceivedData(const DataPacket& packet) {
  QString str = DataFormatter::formatData(*view_settings_, packet);
  text_edit_->appendPlainText(str);
  if(capture_in_progress_) {
    *capture_stream_ << str;
  }
}
