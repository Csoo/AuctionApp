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
        id: main
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
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
            Item {
                width: 296
                height: 100
                scale: 0.96
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
                        passwordCharacter: "●"
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
                    text: qsTr("Sign In")
                    anchors.verticalCenterOffset: 0
                    display: AbstractButton.TextOnly
                    anchors.verticalCenter: userContainer.verticalCenter
                    anchors.left: userContainer.right
                    anchors.leftMargin: 21
                    highlighted: true
                    onClicked: httpRequest.loginRequest(userName.text, password.text) ? applicationWindow.Material.background = "green" : applicationWindow.Material.background =  "red"
                }

                Button {
                    id: registerButton
                    x: 317
                    y: 50
                    width: 90
                    height: userContainer.height
                    text: qsTr("Register")
                    anchors.left: pwContainer.right
                    highlighted: false
                    anchors.verticalCenter: pwContainer.verticalCenter
                    anchors.leftMargin: 21
                    display: AbstractButton.TextOnly
                    onClicked: main.state = "register"
                }

            }
        }
        Item {
            id: register
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
            visible: false

            Item {
                id: container
                width: 289
                height: 372
                anchors.verticalCenterOffset: -104
                anchors.horizontalCenterOffset: -171
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                Item {
                    id: userContainerReg
                    x: 0
                    width: 289
                    height: 40
                    anchors.top: nameContainerReg.bottom
                    anchors.topMargin: 26
                    anchors.bottomMargin: 50
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    opacity: 1
                    visible: true
                    Label {
                        id: userNameTextReg
                        height: parent.height
                        anchors.left: parent.left
                        color: highlightTextColor
                        text: qsTr("User Name")
                        font.weight: Font.Thin
                        font.bold: false
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField {
                        id: userNameReg
                        anchors.right: parent.right
                        width: 200
                        height: parent.height
                        placeholderText: qsTr("name")
                    }

                }
                Item {
                    id: pwContainerReg
                    x: 0
                    width: 289
                    height: 40
                    anchors.top: userContainerReg.bottom
                    anchors.topMargin: 29
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    opacity: 1
                    visible: true
                    Label {
                        id: passwordTextReg
                        height: parent.height
                        color: highlightTextColor
                        anchors.left: parent.left
                        text: qsTr("Password")
                        font.weight: Font.Thin
                        font.bold: false
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField {
                        id: passwordReg
                        x: 96
                        y: 0
                        anchors.right: parent.right
                        width: 200
                        height: parent.height
                        anchors.rightMargin: 0
                        placeholderText: qsTr("password")
                        passwordCharacter: "●"
                        echoMode: hidePassword.checked ? TextInput.Normal : TextInput.Password
                    }
                }

                Item {
                    id: pwConfirmContainerReg
                    x: 0
                    y: 340
                    width: 289
                    height: 40
                    visible: true
                    Label {
                        id: passwordConfTextReg
                        y: 5
                        width: 55
                        height: parent.height
                        color: highlightTextColor
                        text: qsTr("Comfirm Password")
                        anchors.leftMargin: 0
                        wrapMode: Text.WordWrap
                        verticalAlignment: Text.AlignVCenter
                        font.bold: false
                        font.weight: Font.Thin
                        anchors.left: parent.left
                    }

                    TextField {
                        id: passwordConfReg
                        x: 71
                        y: 5
                        width: 200
                        height: parent.height
                        anchors.rightMargin: 0
                        placeholderText: qsTr("password")
                        echoMode: hidePassword.checked ? TextInput.Normal : TextInput.Password
                        anchors.right: parent.right
                        passwordCharacter: "\u25cf"
                    }
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    opacity: 1
                    anchors.top: pwContainerReg.bottom
                    anchors.topMargin: 24
                }

                Item {
                    id: nameContainerReg
                    x: 261
                    y: 126
                    width: 289
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    Label {
                        id: nameTextReg
                        height: parent.height
                        color: highlightTextColor
                        text: qsTr("E-Mail")
                        wrapMode: Text.WordWrap
                        verticalAlignment: Text.AlignVCenter
                        font.bold: false
                        font.weight: Font.Thin
                        anchors.left: parent.left
                    }

                    TextField {
                        id: nameReg
                        width: 200
                        height: parent.height
                        placeholderText: qsTr("e-mail")
                        anchors.right: parent.right
                    }
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    anchors.bottomMargin: 50
                    opacity: 1
                }

                Button {
                    id: backButton
                    x: 201
                    y: 412
                    width: 88
                    height: 40
                    text: qsTr("back")
                    onClicked: main.state = "login"
                }

                Button {
                    id: button
                    x: 0
                    y: 412
                    width: 154
                    height: 40
                    text: qsTr("Register")
                    highlighted: true
                }


            }

            Item {
                id: container1
                x: 7
                y: 2
                width: 289
                height: 372
                Item {
                    id: userContainerReg1
                    x: 1
                    width: 289
                    height: 40
                    Label {
                        id: userNameTextReg1
                        height: parent.height
                        color: highlightTextColor
                        text: qsTr("Address")
                        font.weight: Font.Thin
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                        font.bold: false
                    }

                    TextField {
                        id: userNameReg1
                        width: 200
                        height: parent.height
                        anchors.right: parent.right
                        placeholderText: qsTr("address")
                    }
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    visible: true
                    anchors.top: nameContainerReg1.bottom
                    opacity: 1
                    anchors.bottomMargin: 50
                    anchors.topMargin: 29
                }

                Item {
                    id: pwContainerReg1
                    x: 1
                    width: 289
                    height: 40
                    Label {
                        id: passwordTextReg1
                        height: parent.height
                        color: highlightTextColor
                        text: qsTr("Tel.")
                        font.weight: Font.Thin
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                        font.bold: false
                    }

                    TextField {
                        id: passwordReg1
                        x: 96
                        y: 0
                        width: 200
                        height: parent.height
                        anchors.right: parent.right
                        echoMode: hidePassword.checked ? TextInput.Normal : TextInput.Password
                        passwordCharacter: "\u25cf"
                        placeholderText: qsTr("tel")
                        anchors.rightMargin: 0
                    }
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    visible: true
                    anchors.top: userContainerReg1.bottom
                    opacity: 1
                    anchors.topMargin: 29
                }

                Item {
                    id: pwConfirmContainerReg1
                    x: 0
                    y: 340
                    width: 289
                    height: 40
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    visible: true
                    anchors.top: pwContainerReg1.bottom
                    opacity: 1
                    anchors.topMargin: 24
                }

                Item {
                    id: nameContainerReg1
                    x: 261
                    y: 192
                    width: 289
                    height: 40
                    anchors.horizontalCenterOffset: 1
                    Label {
                        id: nameTextReg1
                        height: parent.height
                        color: highlightTextColor
                        text: qsTr("Full Name")
                        font.weight: Font.Thin
                        wrapMode: Text.WordWrap
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.left
                        font.bold: false
                    }

                    TextField {
                        id: nameReg1
                        width: 200
                        height: parent.height
                        anchors.right: parent.right
                        placeholderText: qsTr("name")
                    }
                    layer.textureSize.height: 0
                    layer.textureSize.width: 0
                    visible: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    opacity: 1
                    anchors.bottomMargin: 50
                }
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: 178
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: -104
            }
        }
    }
}





/*##^##
Designer {
    D{i:38;anchors_x:444}D{i:39;anchors_y:416}D{i:25;anchors_y:264}D{i:40;anchors_y:264}
D{i:24;anchors_height:600;anchors_width:800}
}
##^##*/
