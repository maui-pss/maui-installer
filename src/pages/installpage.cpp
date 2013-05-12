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

#include <QAbstractButton>
#include <QTimer>

#include "installpage.h"
#include "ui_installpage.h"
#include "installer.h"

InstallPage::InstallPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::InstallPage)
{
    setTitle(tr("Installing"));
    ui->setupUi(this);
}

InstallPage::~InstallPage()
{
    delete ui;
}

void InstallPage::initializePage()
{
    Installer *installer = qobject_cast<Installer *>(QApplication::instance());
    Solid::Device device = installer->volumeDevice();

    ui->installInfo->setText(tr("Installing Maui on the disk \"%1\"...")
                             .arg(device.description()));

    QTimer::singleShot(0, this, SLOT(start()));
}

bool InstallPage::isComplete() const
{
    return false;
}

void InstallPage::start()
{
    ui->timeRemaining->setText(tr("Time remaining: Calculating..."));
    wizard()->button(QWizard::BackButton)->setEnabled(false);

#if 0
    QProcess *process = new QProcess(this);
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));
    process->start("/ciao");
#endif
}

void InstallPage::processFinished(int exitCode, QProcess::ExitStatus status)
{
}

#include "moc_installpage.cpp"
