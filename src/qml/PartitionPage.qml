
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Maui.Installer 0.1

Page {
    id: partitionPage
    title: qsTr("Choose installation volume")
    buttonsBar: RowLayout {
        Button {
            action: backAction
        }

        Button {
            action: continueAction
        }
    }

    SystemPalette {
        id: palette
    }

    Action {
        id: backAction
        iconName: "go-previous"
        text: qsTr("Back")
        onTriggered: pageStack.pop(1)
    }

    Action {
        id: continueAction
        iconName: "go-next"
        text: qsTr("Next")
        onTriggered: {
            var component = Qt.createComponent(Qt.resolvedUrl("InstallationPage.qml"));
            var item = component.createObject();
            item.pageStack = pageStack;
            item.volumeUdi = gridView.currentItem.udiField;
            item.volumeLabel = gridView.currentItem.labelField;
            item.deviceName = gridView.currentItem.deviceNameField;
            pageStack.push(item);
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Please choose the volume where Maui will be installed.")
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridView {
                id: gridView
                model: VolumeModel {}
                delegate: Column {
                    property string udiField: udi
                    property string labelField: label
                    property string deviceNameField: deviceName

                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "image://desktoptheme/" + iconName
                        sourceSize: Qt.size(64, 64)
                        width: 64
                        height: 64
                    }

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: label
                    }
                }
                highlight: Rectangle {
                    color: palette.highlight
                }
            }
        }

        Label {
            text: qsTr("A graphical partition manager is not yet available. " +
                       "Open a terminal and use parted to partition your disk.")
        }

        Button {
            text: qsTr("Run Terminal")
            onClicked: installer.runTerminal()
        }
    }
}
