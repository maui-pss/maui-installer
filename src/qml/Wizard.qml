
import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root
    flags: Qt.FramelessWindowHint
    width: 700
    height: 500
    toolBar: Header {
        title: pageStack.currentItem ? pageStack.currentItem.title : ""
        buttonsBar: pageStack.currentItem ? pageStack.currentItem.buttonsBar : []
    }

    StackView {
        id: pageStack
        anchors.fill: parent
        delegate: StackViewDelegate {
            function transitionFinished(properties) {
                properties.exitItem.opacity = 1;
            }

            property Component pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }
        }
        initialItem: WelcomePage {
            pageStack: pageStack
        }
    }
}
