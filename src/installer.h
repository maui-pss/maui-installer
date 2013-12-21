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

#ifndef INSTALLER_H
#define INSTALLER_H

#include <QGuiApplication>

#include <KF5/solid/device.h>

class Installer : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage)
public:
    explicit Installer(int &argc, char *argv[]);

    QString language() const {
        return m_language;
    }

    void setLanguage(const QString &language) {
        m_language = language;
    }

    Solid::Device volumeDevice() const {
        return m_volumeDevice;
    }

    void setVolumeDevice(const Solid::Device &volumeDevice) {
        m_volumeDevice = volumeDevice;
    }

private:
    QString m_language;
    Solid::Device m_volumeDevice;
};

#endif // INSTALLER_H
