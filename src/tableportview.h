#ifndef SRC_TABLEPORTVIEW_H_
#define SRC_TABLEPORTVIEW_H_

#include <QTableWidget>
#include "src/portview.h"

class TablePortView : public PortView {
  Q_OBJECT
 public:
  TablePortView(ViewSettings* view_settings,
                QWidget *parent = 0);

  public slots: //NOLINT
   //! Executed when new data are received
   virtual void OnReceivedData(const DataPacket& packet);

 private:
   //! Text edit of the view
   QTableWidget* table_widget_ {nullptr};

   //! Current row index
   int current_row_idx_ {0};
};

#endif // SRC_TABLEPORTVIEW_H_
