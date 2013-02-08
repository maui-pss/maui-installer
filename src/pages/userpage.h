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

#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWizardPage>

namespace Ui {
    class UserPage;
}

class UserPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit UserPage(QWidget *parent = 0);
    ~UserPage();

    void initializePage();
    bool validatePage();

private:
    Ui::UserPage *ui;

    bool validateRealName() const;
    bool validateHostName() const;
    bool validateUserName() const;
    bool validatePassword1() const;
    bool validatePassword2() const;

private Q_SLOTS:
    void realNameChanged(const QString &text);
    void realNameEdited();
    void hostNameEdited();
    void userNameEdited();
    void password1Edited();
    void password2Edited();
};

#endif // USERPAGE_H
