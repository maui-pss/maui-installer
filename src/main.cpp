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

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include <solid/acadapter.h>
#include <solid/powermanagement.h>

#include "installer.h"
#include "volumemodel.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    // Make sure we use the correct desktop settings
    //setenv("DESKTOP_SESSION", "hawaii", 1);

    Installer app(argc, argv);

    qmlRegisterType<VolumeModel>("Maui.Installer", 0, 1, "VolumeModel");

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(QUrl("qrc:/qml/Wizard.qml"));
    if (!component.isReady()) {
        qWarning("%s", qPrintable(component.errorString()));
        return 1;
    }

    engine.rootContext()->setContextProperty("installer", new Engine(&app));

    QObject *topLevel = component.create();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if (!window) {
        qWarning("Error: your root item has to be a Window!");
        return 1;
    }

    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

#if 0
    // Detect whether AC adapter is plugged or not
    bool isPlugged = false;
    const QList<Solid::Device> list = Solid::Device::listFromType(Solid::DeviceInterface::AcAdapter);
    foreach (const Solid::Device &acAdapterDevice, list) {
        const Solid::AcAdapter *acAdapter = acAdapterDevice.as<Solid::AcAdapter>();
        isPlugged |= acAdapter->isPlugged();
    }

    // Warn about AC adaptater being unplugged
    if (!isPlugged) {
        QMessageBox dialog(&wizard);
        dialog.setIcon(QMessageBox::Warning);
        dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        dialog.setText(Installer::tr("<b>Looks like your power adapter is unplugged</b>"));
        dialog.setInformativeText(Installer::tr(
                                      "Installation is a delicate and lenghty process, "
                                      "hence it's strongly advised to have your PC connected "
                                      "to AC in order to minimize possible risks.<br><br>"
                                      "Would you like to continue?"));
        if (dialog.exec() == QMessageBox::No)
            app.postEvent(&app, new QCloseEvent);
    }
#endif

    window->show();

    return app.exec();
}
