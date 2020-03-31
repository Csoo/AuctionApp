import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Item {
    id: element

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    Column {
        width: 268
        height: 62
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            width: parent.width
            height: parent.height/2
            layer.textureSize.height: 0
            layer.textureSize.width: 0
            opacity: 1
            visible: true
            Label {
                id: userNameText
                height: parent.height
                anchors.left: parent.left
                text: qsTr("User Name")
                font.weight: Font.Normal
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
            width: parent.width
            height: parent.height/2
            layer.textureSize.height: 0
            layer.textureSize.width: 0
            opacity: 1
            visible: true
            Label {
                id: passwordText
                height: parent.height
                anchors.left: parent.left
                text: qsTr("Password")
                font.weight: Font.Normal
                font.bold: true
                verticalAlignment: Text.AlignVCenter
            }
            TextField {
                id: password
                anchors.right: parent.right
                width: 200
                height: parent.height
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
                scale: 0.3
            }
        }

    }

    Button {
        id: button
        x: 493
        y: 209
        width: 78
        height: 32
        text: qsTr("Sing In")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:80;anchors_width:329;anchors_x:36;anchors_y:68}
}
##^##*/
