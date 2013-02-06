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

#include "partitionpage.h"
#include "ui_partitionpage.h"
#include "installer.h"
#include "volumemodel.h"
#include "volumedelegate.h"

PartitionPage::PartitionPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::PartitionPage)
{
    ui->setupUi(this);

    ui->partitions->setModel(new VolumeModel(this));
    ui->partitions->setItemDelegate(new VolumeDelegate(this));

    connect(ui->partitions, SIGNAL(clicked(QModelIndex)),
            this, SLOT(volumeSelected(QModelIndex)));
}

PartitionPage::~PartitionPage()
{
    delete ui;
}

void PartitionPage::initializePage()
{
    ui->mauiIcon->setPixmap(QIcon::fromTheme("start-here").pixmap(196));
}

bool PartitionPage::isComplete() const
{
    VolumeModel *model = qobject_cast<VolumeModel *>(ui->partitions->model());

    if (!m_selectedIndex.isValid())
        return false;

    Installer *installer = qobject_cast<Installer *>(QApplication::instance());
    installer->setVolumeDevice(model->device(m_selectedIndex));
    return true;
}

void PartitionPage::volumeSelected(const QModelIndex &index)
{
    m_selectedIndex = index;
    completeChanged();
}

#include "moc_partitionpage.cpp"
