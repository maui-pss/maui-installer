
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item {
    id: root
    implicitWidth: parent.width
    implicitHeight: contents.height + divider.height + (margin * 2)

    property int margin: 11
    property alias text: label.text
    property string iconName: ""
    property bool checkable: false
    property bool checked: false

    signal clicked

    function __alpha(color, alpha) {
        var newcolor = color;
        newcolor.a = alpha;
        return newcolor;
    }

    onIconNameChanged: {
        if (iconName != "")
            image.source = "image://desktoptheme/" + iconName;
    }

    SystemPalette {
        id: palette
    }

    Rectangle {
        anchors.fill: parent
        color: __alpha(palette.highlight, 127)
        visible: mouse.pressed || (checkable && checked)
    }

    RowLayout {
        id: contents
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 30
        }

        Image {
            id: image
            width: 48
            height: 48
            visible: iconName != ""
        }

        Label {
            id: label
            color: mouse.pressed || (checkable && checked) ? palette.highlightedText : palette.text
            text: modelData
        }
    }

    Rectangle {
        id: divider
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 1
        color: Qt.darker(palette.window, 1.2)
    }

    Image {
        id: arrowImage
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 20
        }
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
            if (root.checkable)
                root.checked = !root.checked;
            root.clicked();
        }
    }
}
