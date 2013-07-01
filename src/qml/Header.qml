
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ToolBar {
    id: root

    property alias title: titleLabel.text
    property alias buttonsBar: buttons.data

    property int margin: 11

    RowLayout {
        id: container
        anchors {
            fill: parent
            margins: margin
        }

        Label {
            id: titleLabel
            font.bold: true
            font.pointSize: 16

            Layout.alignment: Qt.AlignLeft
            Layout.fillHeight: true
        }

        RowLayout {
            id: buttons

            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
        }
    }
}
