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
#include <QRegularExpression>

#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::UserPage)
{
    setTitle(tr("Who are you?"));
    ui->setupUi(this);

    registerField("realName", ui->realName, "text", "textEdited");
    registerField("hostName", ui->hostName, "text", "textEdited");
    registerField("userName", ui->userName, "text", "textEdited");

    connect(ui->realName, SIGNAL(textChanged(QString)),
            this, SLOT(realNameChanged(QString)));
    connect(ui->realName, SIGNAL(textEdited(QString)),
            this, SLOT(realNameEdited()));
    connect(ui->hostName, SIGNAL(textEdited(QString)),
            this, SLOT(hostNameEdited()));
    connect(ui->userName, SIGNAL(textEdited(QString)),
            this, SLOT(userNameEdited()));
    connect(ui->password1, SIGNAL(textEdited(QString)),
            this, SLOT(password1Edited()));
    connect(ui->password2, SIGNAL(textEdited(QString)),
            this, SLOT(password2Edited()));
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::initializePage()
{
    ui->realNameCheck->setVisible(false);
    ui->hostNameCheck->setVisible(false);
    ui->userNameCheck->setVisible(false);
    ui->passwordIndicator->setVisible(false);
    ui->passwordCheck->setVisible(false);
}

bool UserPage::validatePage()
{
    return validateRealName() && validateHostName() && validateUserName()
            && validatePassword1() && validatePassword2();
}

bool UserPage::validateRealName() const
{
    return !ui->realName->text().isEmpty();
}

bool UserPage::validateHostName() const
{
    const QString &text = ui->hostName->text();
    return !(text.isEmpty() ||
             text.contains(QRegularExpression(QStringLiteral("[^a-z0-9-.]"))));
}

bool UserPage::validateUserName() const
{
    const QString &text = ui->userName->text();
    return !(text.isEmpty() ||
             text.contains(QRegularExpression(QStringLiteral("[^a-zA-Z0-9]"))));
}

bool UserPage::validatePassword1() const
{
    return !ui->password1->text().isEmpty();
}

bool UserPage::validatePassword2() const
{
    return ui->password1->text() == ui->password2->text();
}

void UserPage::realNameChanged(const QString &text)
{
    QString newText = text.toLower().replace(QLatin1Char(' '), QStringLiteral(""));
    newText.replace(QRegularExpression(QStringLiteral("[^a-z0-9-]")), QStringLiteral(""));

    ui->hostName->setText(newText);
    Q_EMIT ui->hostName->textEdited(newText);
}

void UserPage::realNameEdited()
{
    ui->realNameCheck->setPixmap(QIcon::fromTheme(validateRealName()
                                                  ? "emblem-ok-symbolic" : "dialog-error").pixmap(16));
    ui->realNameCheck->setVisible(true);
}

void UserPage::hostNameEdited()
{
    ui->hostNameCheck->setPixmap(QIcon::fromTheme(validateHostName()
                                                  ? "emblem-ok-symbolic" : "dialog-error").pixmap(16));
    ui->hostNameCheck->setVisible(true);
}

void UserPage::userNameEdited()
{
    ui->userNameCheck->setPixmap(QIcon::fromTheme(validateUserName()
                                                  ? "emblem-ok-symbolic" : "dialog-error").pixmap(16));
    ui->userNameCheck->setVisible(true);
}

void UserPage::password1Edited()
{
    ui->passwordIndicator->setPixmap(QIcon::fromTheme(validatePassword1()
                                                      ? "emblem-ok-symbolic" : "dialog-error").pixmap(16));
    ui->passwordIndicator->setVisible(true);

    if (!ui->password2->text().isEmpty())
        password2Edited();
}

void UserPage::password2Edited()
{
    ui->passwordCheck->setPixmap(QIcon::fromTheme(validatePassword2()
                                                  ? "emblem-ok-symbolic" : "dialog-error").pixmap(16));
    ui->passwordCheck->setVisible(true);
}

#include "moc_userpage.cpp"
