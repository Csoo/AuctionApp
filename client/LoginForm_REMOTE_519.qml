import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: login
    visible: true
    anchors.fill: parent

    Keys.onPressed: if (event.key === Qt.Key_Return) {httpRequest.loginRequest(userName.text, password.text) ? login.loginAccepted() : wrongLogin.open()}

    signal loginAccepted()

    function loginAction() {
        var responseId = httpRequest.loginRequest(userName.text, password.text)
        console.log(responseId);
        if(responseId === -1) {
            wrongLogin.open();
        }else {
            main.loggedinProfileId = responseId;
            login.loginAccepted();
        }
    }
    function loginIsValid() {
        if (userName.text.length == 0 || password.text.length == 0) {
            signInButton.enabled = false;
        } else {
            signInButton.enabled = true;
        }
    }
    Popup {
        id: wrongLogin
        x: parent.width/2-100
        y: parent.height*0.65
        width: 200
        height: 24
        clip: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Text {
            id: wrongLoginText
            color: "#dfdfdf"
            text: qsTr("Sorry, wrong username or password.")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Auction App")
    }

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
                text: qsTr("Username")
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
                onTextEdited: login.loginIsValid()
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
                onTextEdited: login.loginIsValid()
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
            onClicked: login.loginAction()
            enabled: false
            //onClicked: userName.text == "admin" ? login.loginAccepted() : wrongLogin.open()
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
            onClicked: loggedOutItem.index = 1
        }

    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
