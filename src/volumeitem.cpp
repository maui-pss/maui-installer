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

#include <QtCore/QCoreApplication>
#include <QtCore/QLocale>
#include <QtGui/QIcon>

#include <solid/block.h>

#include "volumeitem.h"
#include "volumemodel.h"

VolumeItem::VolumeItem(const QString &udi, QObject *parent)
    : QObject(parent)
{
    m_device = Solid::Device(udi);
}

QVariant VolumeItem::data(int role)
{
    if (!m_device.isValid())
        return QVariant();

    QPointer<Solid::StorageVolume> volume = m_device.as<Solid::StorageVolume>();

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(m_device.icon());
    case Qt::DisplayRole:
    case VolumeModel::LabelRole:
        return m_device.description();
    case VolumeModel::IconNameRole:
        return m_device.icon();
    case VolumeModel::UdiRole:
        return m_device.udi();
    case VolumeModel::DeviceNameRole: {
        Solid::Block *block = m_device.as<Solid::Block>();
        return block->device();
    }
    case VolumeModel::SizeRole:
        return volume.data()->size();
    case VolumeModel::FormattedSizeRole:
        return representSize(volume.data()->size());
    default:
        break;
    }

    return QVariant();
}

QString VolumeItem::representSize(qulonglong size) const
{
    QLocale locale;

    qreal kib = size / 1024.0;
    if (kib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 bytes", "Bytes format").arg(locale.toString(size));

    qreal mib = kib / 1024.0;
    if (mib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 KiB", "File size format").arg(locale.toString(kib, 'f', 3));

    qreal gib = mib / 1024.0;
    if (gib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 MiB", "File size format").arg(locale.toString(mib, 'f', 3));

    qreal tib = gib / 1024.0;
    if (tib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 GiB", "File size format").arg(locale.toString(gib, 'f', 3));

    qreal pib = tib / 1024.0;
    if (pib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 TiB", "File size format").arg(locale.toString(tib, 'f', 3));

    return QCoreApplication::translate(
                "VolumeDelegate",
                "%1 PiB", "File size format").arg(locale.toString(pib, 'f', 3));
}

#include "moc_volumeitem.cpp"
