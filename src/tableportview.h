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

#ifndef SRC_TABLEPORTVIEW_H_
#define SRC_TABLEPORTVIEW_H_

#include <QTableWidget>
#include "src/portview.h"

class TablePortView : public PortView {
  Q_OBJECT

 public:
  //! Constructor
  TablePortView(ViewSettings* view_settings,
                QWidget *parent = 0);

 public slots: //NOLINT
  //! Executed when new data are received
  virtual void TreatDataPacket(DataPacket packet);

  virtual void OnDataSent(DataPacket packet);

 private:
  //! Text edit of the view
  QTableWidget* table_widget_ {nullptr};

  //! Current row index
  int current_row_idx_ {0};
};

#endif  // SRC_TABLEPORTVIEW_H_
