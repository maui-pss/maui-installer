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
#include <QWizard>
#include <QCloseEvent>
#include <solid/acadapter.h>
#include <solid/powermanagement.h>

#include "installer.h"
#include "pages/welcomepage.h"
#include "pages/partitionpage.h"
#include "pages/installpage.h"
#include "pages/thankspage.h"

int main(int argc, char *argv[])
{
    // Make sure we use the correct desktop settings
    setenv("DESKTOP_SESSION", "hawaii", 1);

    Installer app(argc, argv);

    // Setup wizard
    QWizard wizard;
    wizard.addPage(new WelcomePage(&wizard));
    wizard.addPage(new PartitionPage(&wizard));
    wizard.addPage(new InstallPage(&wizard));
    wizard.addPage(new ThanksPage(&wizard));
    wizard.show();

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

    return app.exec();
}
