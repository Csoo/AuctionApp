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

    property bool loading: false

    function registering(userName, password, email, fullName, address, phone) {
        backButton.enabled = false;
        var error = false;
        var emailRegx = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        var phoneRegx = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/im;
        //Valid formats:
        /*(123) 456-7890
        (123)456-7890
        123-456-7890
        123.456.7890
        1234567890
        +31636363634
        075-63546725*/
        if (userName === "" || userName.search(" ") !== -1 || userName.search("\'") !== -1 || userName.search("\"") !== -1) {
            userNameTextReg.color = "red";
            error = true;
        } else {
            userNameTextReg.color = applicationWindow.highlightTextColor;
        }
        if (password === "" || password.search(" ") !== -1 || password.search("\'") !== -1 || password.search("\"") !== -1) {
            passwordTextReg.color = "red";
            error = true;
        } else {
            passwordTextReg.color = applicationWindow.highlightTextColor;
        }
        if (password === "" || password !== passwordConfReg.text) {
            passwordConfTextReg.color = "red";
            error = true;
        } else {
            passwordConfTextReg.color = applicationWindow.highlightTextColor;
        }
        if (emailRegx.test(String(email).toLowerCase()) === false) {
            emailTextReg.color = "red";
            error = true;
        } else {
            emailTextReg.color = applicationWindow.highlightTextColor;
        }
        if (fullName === "") {
            fullNameTextReg.color = "red";
            error = true;
        } else {
            fullNameTextReg.color = applicationWindow.highlightTextColor;
        }
        if (address === "") {
            addressTextReg.color = "red";
            error = true;
        } else {
            addressTextReg.color = applicationWindow.highlightTextColor;
        }
        if (phone !== "" && phoneRegx.test(String(phone).toLowerCase()) === false) {
            phoneTextReg.color = "red";
            error = true;
        } else {
            phoneTextReg.color = applicationWindow.highlightTextColor;
        }

        if (error) {
            backButton.enabled = true;
            return;
        }

        register.loading = true;
        if (httpRequest.registerRequest(userName, password, email, fullName, address, phone) ) {
            okRegistration.open()
        } else {
            wrongRegistration.open();
        }
        register.loading = false;
        backButton.enabled = true;
    }

    BusyIndicator {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        running: loading
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Registration")
    }

    Popup {
        id: okRegistration
        x: parent.width/2-100
        y: parent.height*0.85
        width: 200
        height: 24
        clip: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Text {
            id: okRegistrationText
            color: "#dfdfdf"
            text: qsTr("Successfull registration!.")
            styleColor: "#209a14"
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Popup {
        id: wrongRegistration
        x: parent.width/2-120
        y: parent.height*0.85
        width: 240
        height: 32
        clip: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Text {
            id: wrongRegistrationText
            color: "#dfdfdf"
            text: qsTr("This username or e-mail address is already used. Please check if you registerd before.")
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

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
                text: qsTr("Username")
                font.weight: Font.Thin
                font.bold: false
                verticalAlignment: Text.AlignVCenter
            }
            TextField {
                id: userNameReg
                anchors.right: parent.right
                width: 200
                height: parent.height
                placeholderText: qsTr("username")
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
                id: emailTextReg
                height: parent.height
                color: highlightTextColor
                text: qsTr("E-mail")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                font.bold: false
                font.weight: Font.Thin
                anchors.left: parent.left
            }

            TextField {
                id: emailReg
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
            onClicked: register.registering(userNameReg.text, passwordReg.text, emailReg.text, fullNameReg.text, addressReg.text, phoneReg.text)
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
                id: addressTextReg
                height: parent.height
                color: highlightTextColor
                text: qsTr("Address")
                font.weight: Font.Thin
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                font.bold: false
            }

            TextField {
                id: addressReg
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
                id: phoneTextReg
                height: parent.height
                color: highlightTextColor
                text: qsTr("Tel. (optional)")
                font.weight: Font.Thin
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                font.bold: false
            }

            TextField {
                id: phoneReg
                x: 96
                y: 0
                width: 200
                height: parent.height
                anchors.right: parent.right
                passwordCharacter: "\u25cf"
                placeholderText: qsTr("phone number")
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
                id: fullNameTextReg
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
                id: fullNameReg
                width: 200
                height: parent.height
                anchors.right: parent.right
                placeholderText: qsTr("full name")
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
