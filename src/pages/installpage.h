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

#ifndef INSTALLPAGE_H
#define INSTALLPAGE_H

#include <QWizardPage>

namespace Ui {
    class InstallPage;
}

class InstallPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit InstallPage(QWidget *parent = 0);
    ~InstallPage();

    void initializePage();
    bool isComplete() const;

private:
    Ui::InstallPage *ui;

private Q_SLOTS:
    void start();
    void processFinished(int exitCode, QProcess::ExitStatus status);
};

#endif // INSTALLPAGE_H
