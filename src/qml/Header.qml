
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ToolBar {
    id: root

    property alias title: titleLabel.text
    property alias buttonsBar: buttons.data

    property int margin: 11

    Item {
        id: container
        anchors {
            fill: parent
            margins: margin
        }

        Label {
            id: titleLabel
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
            }
            font.bold: true
            font.pointSize: 16
            width: parent.width - buttons.width - (margin * 2)
        }

        Item {
            id: buttons
            anchors {
                top: parent.top
                right: parent.right
                bottom: parent.bottom
            }
            width: childrenRect.width
        }
    }
}
