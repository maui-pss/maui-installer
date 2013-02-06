/****************************************************************************
 * This file is part of Maui Installer.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QIcon>
#include <QPixmap>

#include "thankspage.h"
#include "ui_thankspage.h"

ThanksPage::ThanksPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ThanksPage)
{
    setTitle(tr("Thank You"));
    ui->setupUi(this);
}

ThanksPage::~ThanksPage()
{
    delete ui;
}

void ThanksPage::initializePage()
{
    ui->computerIcon->setPixmap(QIcon::fromTheme("computer").pixmap(256));
}

#include "moc_thankspage.cpp"
