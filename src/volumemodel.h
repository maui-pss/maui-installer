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

#ifndef VOLUMEMODEL_H
#define VOLUMEMODEL_H

#include <QAbstractListModel>

#include <solid/predicate.h>

class QStringList;

namespace Solid {
    class DeviceNotifier;
    class StorageVolume;
}

class VolumeItem;

class VolumeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(VolumeRole)
public:
    enum VolumeRole {
        UdiRole = Qt::UserRole + 1
    };

    explicit VolumeModel(QObject *parent = 0);

    QIcon icon(const QModelIndex &index) const;

    QString text(const QModelIndex &index) const;

    Solid::Device device(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;

    int rowCount(const QModelIndex &parent) const;

private:
    Solid::Predicate m_predicate;
    Solid::DeviceNotifier *m_notifier;
    QStringList m_availableDevices;
    QList<VolumeItem *> m_items;

    void reloadDevices();

private Q_SLOTS:
    void deviceAdded(const QString &udi);
    void deviceRemoved(const QString &udi);
};

#endif // VOLUMEMODEL_H
