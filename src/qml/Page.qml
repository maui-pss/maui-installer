
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item {
    property StackView pageStack

    property string title
    default property alias content: container.data
    property Item buttonsBar

    property int margin: 11

    Image {
        anchors.fill: parent
        source: "qrc:/images/noise-texture.png"
        sourceSize: Qt.size(100, 100)
        fillMode: Image.Tile

        Item {
            id: container
            anchors {
                fill: parent
                margins: margin
            }
        }
    }
}
