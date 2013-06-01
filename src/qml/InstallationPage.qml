
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Page {
    id: installationpage
    title: qsTr("Maui installation")

    property string volumeUdi
    property string volumeLabel
    property string deviceName

    ColumnLayout {
        anchors.fill: parent

        Timer {
            running: true
            interval: 1000
            repeat: true
            onTriggered: progressBar.value += 0.1
        }

        Image {
            source: "qrc:/images/m.png"
            fillMode: Image.PreserveAspectFit

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }

        Label {
            text: qsTr("Installing Maui on the disk \"%1\"...").arg(volumeLabel)
            font.bold: true
        }

        ProgressBar {
            id: progressBar
            value: 0
            Layout.fillWidth: true
        }
    }
}
