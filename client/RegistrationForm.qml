import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: register
    anchors.rightMargin: 0
    anchors.bottomMargin: 0
    anchors.leftMargin: 0
    anchors.topMargin: 0
    anchors.fill: parent
    visible: true

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
            onClicked: loggedOutItem.index = 0
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
