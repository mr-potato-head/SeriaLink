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

#include <QDir>
#include <QFileDialog>
#include "src/menuwidget.h"
#include "src/aboutwindow.h"

MenuWidget::MenuWidget(Session* session,
                       QWidget *parent)
  : QWidget(parent),
    session_(session) {
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

  open_session_button_ = new QPushButton(this);
  open_session_button_->setIcon(QIcon(":/icons/icons/folder-8x.png"));
  open_session_button_->setFixedSize(200, 60);

  save_session_button_ = new QPushButton(this);
  save_session_button_->setIcon(QIcon(":/icons/icons/hard-drive-8x.png"));
  save_session_button_->setFixedSize(200, 60);

  about_button_ = new QPushButton(this);
  about_button_->setIcon(QIcon(":/icons/icons/question-mark-8x.png"));
  about_button_->setFixedSize(200, 60);

  main_layout_ = new QGridLayout(this);
  main_layout_->addWidget(open_session_button_, 0, 0);
  main_layout_->addWidget(save_session_button_, 1, 0);
  main_layout_->addWidget(about_button_, 2, 0);

  connect(open_session_button_, &QPushButton::clicked, [=](void) {
    // Choose session file
    QString fileName =
        QFileDialog::getOpenFileName(this,
                                     tr("Open session file"),
                                     QDir::homePath(),
                                     tr("Session files (*.json)"));

    // Close menu
    this->close();

    // Load session
    session_->LoadFromFile(fileName);
  });

  connect(save_session_button_, &QPushButton::clicked, [=](void) {
    // Choose session file
    QString fileName =
        QFileDialog::getSaveFileName(this,
                                     tr("Open session file"),
                                     QDir::homePath(),
                                     tr("Session files (*.json)"));

    // Close menu
    this->close();

    // Load session
    session_->SaveInFile(fileName);
  });

  connect(about_button_, &QPushButton::clicked, [=](void) {
    AboutWindow* about = new AboutWindow();
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->exec();
    this->close();
  });
}
