#ifndef TERMINALPORTVIEW_H
#define TERMINALPORTVIEW_H

#include <QPlainTextEdit>
#include "src/portview.h"

class TerminalPortView : public PortView {
  Q_OBJECT

 public:
  TerminalPortView(ViewSettings* view_settings,
                   QWidget *parent = 0);

 public slots: //NOLINT
  //! Executed when new data are received
  virtual void OnReceivedData(const DataPacket& packet);

 private:
  //! Text edit of the view
  QPlainTextEdit* text_edit_ {nullptr};
};

#endif // TERMINALPORTVIEW_H
