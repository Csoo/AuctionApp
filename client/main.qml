import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 800
    height: 600
    minimumWidth: 450
    minimumHeight: 300
    title: qsTr("Auction Application")

    property bool isDark: dark.checked ? true : false
    property color highlightTextColor: isDark ? "#90CAF9" : "#2196F3"

    Material.theme: isDark ? Material.Dark : Material.Light
    Material.accent: Material.Blue

    MenuBar {
        transformOrigin: Item.TopLeft
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
        id: main
        anchors.fill: parent

        states: [
            State {
                name: "register"
                PropertyChanges { target: login; visible: false }
                PropertyChanges { target: register; visible: true }
            },
            State {
                name: "login"
                PropertyChanges { target: login; visible: true }
                PropertyChanges { target: register; visible: false }
            }
        ]

        Item {
            id: login
            visible: true
            anchors.fill: parent
            Column {
                id: column
                width: 296
                height: 100
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: -50
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                Item {
                    id: userContainer
                    width: parent.width
                    height: parent.height/2
                    anchors.bottomMargin: 50
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    opacity: 1
                    visible: true
                    Label {
                        id: userNameText
                        height: parent.height
                        anchors.left: parent.left
                        color: highlightTextColor
                        text: qsTr("User Name")
                        font.weight: Font.Medium
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField {
                        id: userName
                        anchors.right: parent.right
                        width: 200
                        height: parent.height
                        placeholderText: qsTr("name")
                    }

                }
                Item {
                    id: pwContainer
                    width: parent.width
                    height: parent.height/2
                    anchors.top: userContainer.bottom
                    anchors.topMargin: 0
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    opacity: 1
                    visible: true
                    Label {
                        id: passwordText
                        height: parent.height
                        color: highlightTextColor
                        anchors.left: parent.left
                        text: qsTr("Password")
                        font.weight: Font.Medium
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField {
                        id: password
                        x: 96
                        y: 0
                        anchors.right: parent.right
                        width: 200
                        height: parent.height
                        anchors.rightMargin: 0
                        placeholderText: qsTr("password")
                        passwordCharacter: "∎"
                        echoMode: hidePassword.checked ? TextInput.Normal : TextInput.Password
                    }

                    Switch {
                        id: hidePassword
                        width: 60
                        height: parent.height
                        display: AbstractButton.IconOnly
                        antialiasing: true
                        anchors.rightMargin: -13
                        anchors.right: parent.right
                        scale: 0.6
                    }
                }

                Button {
                    id: signInButton
                    width: 90
                    height: userContainer.height
                    text: qsTr("Sing In")
                    display: AbstractButton.TextOnly
                    anchors.verticalCenter: userContainer.verticalCenter
                    anchors.left: userContainer.right
                    anchors.leftMargin: 21
                    highlighted: true
                    onClicked: main.state = "register"
                }

                Button {
                    id: registerButton
                    width: 90
                    height: userContainer.height
                    text: qsTr("Register")
                    anchors.left: pwContainer.right
                    highlighted: false
                    anchors.verticalCenter: pwContainer.verticalCenter
                    anchors.leftMargin: 21
                    display: AbstractButton.TextOnly
                }

            }
         }
        Item {
            id: register
            visible: false
            anchors.fill: parent
            Button {
                id: backButton
                x: 350
                y: 280
                text: qsTr("back")

                onClicked: main.state = "login"
            }
        }
     }
}




