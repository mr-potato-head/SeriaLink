#ifndef SRC_DUMPPORTVIEW_H_
#define SRC_DUMPPORTVIEW_H_

#include <QPlainTextEdit>
#include "src/portview.h"

class DumpPortView : public PortView {
  Q_OBJECT

 public:
  DumpPortView(ViewSettings* view_settings,
               QWidget *parent = 0);

 public slots: //NOLINT
  //! Executed when new data are received
  virtual void OnReceivedData(const DataPacket& packet);

 private:
  //! Text edit of the view
  QPlainTextEdit* text_edit_ {nullptr};
};

#endif // SRC_DUMPPORTVIEW_H_
