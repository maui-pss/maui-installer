
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0

Page {
    id: userPage
    title: qsTr("User information")
    buttonsBar: RowLayout {
        Button {
            action: backAction
        }

        Button {
            action: nextAction
        }
    }

    Action {
        id: backAction
        iconName: "go-previous"
        text: qsTr("Back")
        onTriggered: pageStack.pop(1)
    }

    Action {
        id: nextAction
        iconName: "go-next"
        text: qsTr("Next")
        onTriggered: {
            var component = Qt.createComponent(Qt.resolvedUrl("qrc:/qml/PartitionPage.qml"));
            var item = component.createObject();
            item.pageStack = pageStack;
            pageStack.push(item);
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            flow: GridLayout.TopToBottom
            rows: 4

            Label {
                text: qsTr("Your name:")
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
            Label {
                text: qsTr("User name:")
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
            Label {
                text: qsTr("Password:")
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
            Label {
                text: qsTr("Password confirmation:")
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }

            TextField {
                id: fullName
                placeholderText: qsTr("First and last name")
                Layout.fillWidth: true
            }
            TextField {
                id: userName
                placeholderText: qsTr("User name to log into the system")
                Layout.preferredWidth: 250
            }
            TextField {
                id: password1
                placeholderText: qsTr("Password")
                Layout.preferredWidth: 150
            }
            TextField {
                id: password2
                placeholderText: qsTr("Password")
                Layout.preferredWidth: 150
            }
        }
    }
}
