import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: profileWindow
    visible: true
    width: 1280
    height: 720
    minimumWidth: 450
    minimumHeight: 300
    title: qsTr("Profile")

    property bool isDark: dark.checked ? true : false
    property color highlightTextColor: isDark ? "#90CAF9" : "#2196F3"

    Material.theme: isDark ? Material.Dark : Material.Light
    Material.accent: Material.Blue

    MenuBar {
        x: 0
        y: 0
        transformOrigin: Item.TopLeft
        width: parent.width*1.25
        scale: 0.8

        Menu {
            title: qsTr("Options")
            MenuBarItem {id: dark; text: qsTr("Dark"); checked: true; checkable: true; transformOrigin: Item.TopLeft; scale: 0.8
                CheckBox {
                    hoverEnabled: false
                    enabled: false
                    checkable: false
                    checked: parent.checked
                    anchors.right: parent.right

                }
            }
            MenuBarItem {text: qsTr("Quit"); rightPadding: 6; leftPadding: 12; transformOrigin: Item.TopLeft; scale: 0.8
                onClicked: Qt.quit()
            }
        }




    }


    Item {
        id: menu
        x: 0
        y: 40
        width: 200
        height: 680

        Button {
            id: button
            x: 0
            y: 323
            width: 200
            height: 45
            text: qsTr("Adatok módosítása")
            display: AbstractButton.TextBesideIcon
            highlighted: false
        }

        Button {
            id: button1
            x: 0
            y: 620
            width: 200
            height: 60
            text: qsTr("Kijelentkezés")
            display: AbstractButton.TextBesideIcon
        }
    }

    Item {
        id: profile
        x: 218
        y: 30
        width: 1080
        height: 680

        Image {
            id: image
            x: 118
            y: 78
            width: 163
            height: 189
            sourceSize.height: 400
            sourceSize.width: 200
            source: ""
            fillMode: Image.Stretch
        }

        Text {
            id: element
            x: 118
            y: 307
            width: 127
            height: 24
            text: qsTr("Felhasználónév: ")
            font.pixelSize: 18
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_x:"-160"}
}
##^##*/
