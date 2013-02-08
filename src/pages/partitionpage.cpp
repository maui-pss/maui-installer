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

#include <QMessageBox>
#include <QPointer>

#include <solid/storagevolume.h>

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

bool PartitionPage::validatePage()
{
    VolumeModel *model = qobject_cast<VolumeModel *>(ui->partitions->model());
    Solid::Device device = model->device(m_selectedIndex);
    QPointer<Solid::StorageVolume> volume = device.as<Solid::StorageVolume>();

    if (volume->size() < (1024 * 1024 * 1024)) {
        QMessageBox dialog(this);
        dialog.setIcon(QMessageBox::Critical);
        dialog.setText(tr("<b>\"%1\" doesn't have enough space available</b>").arg(device.description()));
        dialog.setInformativeText(tr("The selected partition has not enough free space, "
                                     "Maui requires at least 1 GiB. Please select "
                                     "another partition and try again."));
        dialog.exec();
        return false;
    }

    return true;
}

void PartitionPage::volumeSelected(const QModelIndex &index)
{
    m_selectedIndex = index;
    Q_EMIT completeChanged();
}

#include "moc_partitionpage.cpp"
