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
#include <QStringList>

#include <solid/device.h>
#include <solid/devicenotifier.h>
#include <solid/storagevolume.h>

#include "volumemodel.h"
#include "volumeitem.h"

VolumeModel::VolumeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_predicate = Solid::Predicate::fromString(
                QString::fromUtf8(
                    "[[ StorageVolume.ignored == false AND "
                    "[ StorageVolume.usage == 'FileSystem' OR "
                    "StorageVolume.usage == 'Encrypted' ]] AND "
                    "[ IS StorageAccess AND StorageVolume.fsType == 'ext4' ]]"
                    ));
    Q_ASSERT(m_predicate.isValid());

    m_notifier = Solid::DeviceNotifier::instance();
    connect(m_notifier, SIGNAL(deviceAdded(QString)), this, SLOT(deviceAdded(QString)));
    connect(m_notifier, SIGNAL(deviceRemoved(QString)), this, SLOT(deviceRemoved(QString)));

    const QList<Solid::Device> &list = Solid::Device::listFromQuery(m_predicate);
    for (int i = 0; i < list.size(); i++)
        m_availableDevices << list.at(i).udi();
    reloadDevices();
}

QIcon VolumeModel::icon(const QModelIndex &index) const
{
    return QIcon(data(index, Qt::DecorationRole).value<QIcon>());
}

QString VolumeModel::text(const QModelIndex &index) const
{
    return data(index, Qt::DisplayRole).toString();
}

QPointer<Solid::StorageVolume> VolumeModel::volume(const QModelIndex &index)
{
    VolumeItem *item = m_items.at(index.row());
    return item->volume();
}

QVariant VolumeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    VolumeItem *item = m_items.at(index.row());
    return item->data(role);
}

int VolumeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_availableDevices.size();
}

void VolumeModel::reloadDevices()
{
    // FIXME: This is not the best code in the world...

    beginRemoveRows(QModelIndex(), 0, m_items.size());
    foreach (VolumeItem *item, m_items) {
        item->deleteLater();
        m_items.removeOne(item);
    }
    endRemoveRows();

    beginInsertRows(QModelIndex(), m_items.size(), m_availableDevices.size());
    foreach (QString udi, m_availableDevices) {
        VolumeItem *item = new VolumeItem(udi, this);
        m_items.append(item);
    }
    endInsertRows();
}

void VolumeModel::deviceAdded(const QString &udi)
{
    Solid::Device device(udi);

    if (m_predicate.matches(device)) {
        m_availableDevices << udi;
        reloadDevices();
    }
}

void VolumeModel::deviceRemoved(const QString &udi)
{
    if (m_availableDevices.contains(udi)) {
        m_availableDevices.removeOne(udi);
        reloadDevices();
    }
}

#include "moc_volumemodel.cpp"
