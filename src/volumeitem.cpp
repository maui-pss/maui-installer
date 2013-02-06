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

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(m_device.icon());
    case Qt::DisplayRole:
        return m_device.description();
    case VolumeModel::UdiRole:
        return m_device.udi();
    default:
        break;
    }

    return QVariant();
}

#include "moc_volumeitem.cpp"
