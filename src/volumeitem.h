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

#ifndef VOLUMEITEM_H
#define VOLUMEITEM_H

#include <QObject>
#include <QPointer>

#include <solid/device.h>
#include <solid/storagevolume.h>

class VolumeItem : public QObject
{
    Q_OBJECT
public:
    explicit VolumeItem(const QString &udi, QObject *parent = 0);

    Solid::Device device() const {
        return m_device;
    }

    QPointer<Solid::StorageVolume> volume() {
        return m_device.as<Solid::StorageVolume>();
    }

    QVariant data(int role);

private:
    Solid::Device m_device;

    QString representSize(qulonglong size) const;
};

#endif // VOLUMEITEM_H
