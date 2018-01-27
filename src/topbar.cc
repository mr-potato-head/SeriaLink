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

#include "src/topbar.h"
#include "src/addormodifyportdialog.h"
#include "src/comport.h"
#include "src/session.h"

TopBar::TopBar(QWidget *parent)
  : QWidget(parent) {
  page_selector_ = new PageSelector(this);
  page_switcher_ = new PageSwitcher(this);
  main_layout_ = new QHBoxLayout(this);
  main_layout_->addWidget(page_selector_);
  main_layout_->addWidget(page_switcher_);

  main_layout_->setStretchFactor(static_cast<QWidget*>(page_selector_), 70);
  main_layout_->setStretchFactor(static_cast<QWidget*>(page_switcher_), 30);

  main_layout_->setMargin(0);
  main_layout_->setSpacing(0);

  connect(page_switcher_, SIGNAL(IncreaseCurrentPageIndex()),
          this, SLOT(OnIncreaseCurrentPageIndex()));
  connect(page_switcher_, SIGNAL(DecreaseCurrentPageIndex()),
          this, SLOT(OnDecreaseCurrentPageIndex()));
  connect(page_switcher_, SIGNAL(AddPage()),
          this, SLOT(openAddOrModifyDialog()));
//  connect(session_, SIGNAL(PageAdded(int)),
//          page_selector_, SLOT(AddButton(int)));
//  connect(session_, SIGNAL(IndexChanged(int)),
//          this, SLOT(UpdateSelectorButtonStatus()));
//  connect(session_, SIGNAL(IndexChanged(int)),
//          this, SLOT(UpdateSwitcherButtonStatus()));
  connect(page_switcher_, SIGNAL(OpenMenu()),
          this, SIGNAL(OpenMenu()));

  //UpdateSwitcherButtonStatus();
}

void TopBar::SetSession(Session* session) {
  session_ = session;
  page_selector_->SetSession(session);
  page_switcher_->SetSession(session);
}

void TopBar::AddPageButton(void) {
  page_selector_->AddButton();
}

void TopBar::DeletePageButton(int page_idx) {
  page_selector_->DeleteButton(page_idx);
  UpdateSwitcherButtonStatus();
  UpdateSelectorButtonStatus();
}

void TopBar::UpdatePageButtonName(int page_idx) {
  page_selector_->UpdateButtonName(page_idx);
}

void TopBar::OnIncreaseCurrentPageIndex(void) {
  int current_page_index = session_->GetCurrentPageIndex();
  current_page_index++;
  session_->SetCurrentPageIndex(current_page_index);

  UpdateSwitcherButtonStatus();
  UpdateSelectorButtonStatus();
}

void TopBar::OnDecreaseCurrentPageIndex(void) {
  int current_page_index = session_->GetCurrentPageIndex();
  current_page_index--;
  session_->SetCurrentPageIndex(current_page_index);

  UpdateSwitcherButtonStatus();
  UpdateSelectorButtonStatus();
}

void TopBar::UpdateSwitcherButtonStatus(void) {
  int page_number = session_->GetPortPageList()->size();
  int current_page_index = session_->GetCurrentPageIndex();

  if (page_number <= 1) {
    page_switcher_->DisableButton(PageSwitcher::ButtonType::kIncreaseButton);
    page_switcher_->DisableButton(PageSwitcher::ButtonType::kDecreaseButton);
  } else {
    if (current_page_index >= (page_number-1)) {
      page_switcher_->DisableButton(PageSwitcher::ButtonType::kIncreaseButton);
      page_switcher_->EnableButton(PageSwitcher::ButtonType::kDecreaseButton);
    } else if (current_page_index == 0) {
      page_switcher_->DisableButton(PageSwitcher::ButtonType::kDecreaseButton);
      page_switcher_->EnableButton(PageSwitcher::ButtonType::kIncreaseButton);
    } else {
      page_switcher_->EnableButton(PageSwitcher::ButtonType::kIncreaseButton);
      page_switcher_->EnableButton(PageSwitcher::ButtonType::kDecreaseButton);
    }
  }
}

void TopBar::UpdateSelectorButtonStatus(void) {
  int current_page_index = session_->GetCurrentPageIndex();
  if(current_page_index >= 0) {
    page_selector_->SetCheckedState(current_page_index);
  }
}

void TopBar::openAddOrModifyDialog(void) {
  ComPortSettings* port_settings = new ComPortSettings();
  AddOrModifyPortDialog addDialog(port_settings,
                                  AddOrModifyPortDialog::ActionType::kAdd,
                                  this);
  qint32 result = addDialog.exec();

  switch (result) {
    case QDialog::Accepted:
    {
      // Add port in session
      session_->AddPage(port_settings);

      UpdateSwitcherButtonStatus();
      UpdateSelectorButtonStatus();
      break;
    }
    case QDialog::Rejected:
    default:
    break;
  }
}
