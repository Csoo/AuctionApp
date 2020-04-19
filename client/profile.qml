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
        height: 40
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
        y: 33
        width: 200
        height: 687

        Button {
            id: changedata
            x: 0
            y: 261
            width: 200
            height: 45
            text: qsTr("Change User Data")
            font.pointSize: 12
            font.capitalization: Font.MixedCase
            font.family: "Arial"
            display: AbstractButton.TextBesideIcon
            highlighted: false
        }

        Button {
            id: button1
            x: 0
            y: 627
            width: 200
            height: 60
            text: qsTr("Logout")
            font.pointSize: 14
            font.capitalization: Font.MixedCase
            display: AbstractButton.TextBesideIcon
        }

        Button {
            id: changepwd
            x: 0
            y: 337
            width: 200
            height: 45
            text: qsTr("Change Password")
            display: AbstractButton.TextBesideIcon
            font.pointSize: 12
            highlighted: false
            font.family: "Arial"
            font.capitalization: Font.MixedCase
        }
    }

    Item {
        id: profile
        x: 200
        y: 30
        width: 1080
        height: 690

        Image {
            id: image
            x: 118
            y: 78
            width: 163
            height: 189
            clip: true
            visible: true
            sourceSize.height: 443
            sourceSize.width: 309
            source: "c:/Users/stecs/Pictures/Clipboard01.jpg"
            fillMode: Image.Stretch
        }

        Text {
            id: username_tag
            x: 118
            y: 307
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Username: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: username
            x: 232
            y: 307
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: fullname_tag
            x: 118
            y: 335
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Full Name:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: fullname
            x: 232
            y: 335
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: email_tag
            x: 118
            y: 361
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("E-mail:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: email
            x: 232
            y: 361
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: createtime_tag
            x: 118
            y: 474
            width: 140
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Account created at: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: createtime
            x: 290
            y: 474
            width: 133
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: address_tag
            x: 118
            y: 387
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Address:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: address
            x: 232
            y: 387
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: phone_tag
            x: 118
            y: 413
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Phone:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: phone
            x: 232
            y: 413
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: lastlogin_tag
            x: 118
            y: 500
            width: 140
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Last login: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: lastlogin
            x: 290
            y: 500
            width: 133
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: positive_tag
            x: 666
            y: 307
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Positive: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: positive
            x: 780
            y: 307
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: negative_tag
            x: 666
            y: 335
            width: 93
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Negative: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Text {
            id: negative
            x: 780
            y: 335
            width: 152
            height: 20
            color: isDark ? "#FFFFFF" : "#000000"
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Text {
            id: reviews_tag
            x: 666
            y: 253
            text: qsTr("Reviews:")
            color: isDark ? "#FFFFFF" : "#000000"
            font.bold: true
            font.pixelSize: 17
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_x:"-160"}
}
##^##*/
