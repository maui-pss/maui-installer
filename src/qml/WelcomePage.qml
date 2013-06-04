
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import Maui.Installer 0.1

Page {
    id: welcomePage
    title: qsTr("Welcome to Maui installation")
    buttonsBar: RowLayout {
        Button {
            action: tryAction
        }

        Button {
            action: nextAction
        }
    }

    Action {
        id: tryAction
        iconName: "user-desktop"
        text: qsTr("Try Maui")
        onTriggered: console.log("try")
    }

    Action {
        id: nextAction
        iconName: "go-next"
        text: qsTr("Install Maui")
        onTriggered: {
            var component = Qt.createComponent(Qt.resolvedUrl("qrc:/qml/UserPage.qml"));
            var item = component.createObject();
            item.pageStack = pageStack;
            pageStack.push(item);
        }
    }

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            text: qsTr("<p>You can try Maui without making any changes to your computer, directly from this media.</p><br>" +
                       "<p>Or if you're ready, you can install Maui alongside (or instead of) your current operating system.</p>" +
                       "<p>This shouldn't take too long.</p><br>" +
                       "<p>You may wish to read the <a href=\"RELNOTES\">release notes</a>.</p>")
            //wrapMode: Text.WrapAnywhere
        }

        TableView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            alternatingRowColors: false
            headerVisible: false
            model: LanguagesModel {}

            TableViewColumn { role: "name" }
        }
    }
}
