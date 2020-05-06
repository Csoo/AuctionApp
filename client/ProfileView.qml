 import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: profile
    x: 0
    y: 0
    width: 1080
    height: 690

    Component.onCompleted: profile.getUserData(1)

    function getUserData(id) {
        //httpRequest.userDataRequest(id);
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Profile")
    }

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
        source: "img/profil.png"
        fillMode: Image.Stretch
    }

    Label {
        id: username_tag
        x: 118
        y: 307
        width: 93
        height: 20
        text: qsTr("Username: ")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: username
        x: 232
        y: 307
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: fullname_tag
        x: 118
        y: 335
        width: 93
        height: 20
        text: qsTr("Full Name:")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: fullname
        x: 232
        y: 335
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: email_tag
        x: 118
        y: 361
        width: 93
        height: 20
        text: qsTr("E-mail:")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: email
        x: 232
        y: 361
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: createtime_tag
        x: 118
        y: 474
        width: 140
        height: 20
        text: qsTr("Account created at: ")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: createtime
        x: 290
        y: 474
        width: 133
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: address_tag
        x: 118
        y: 387
        width: 93
        height: 20
        text: qsTr("Address:")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: address
        x: 232
        y: 387
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: phone_tag
        x: 118
        y: 413
        width: 93
        height: 20
        text: qsTr("Phone:")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: phone
        x: 232
        y: 413
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: lastlogin_tag
        x: 118
        y: 500
        width: 140
        height: 20
        text: qsTr("Last login: ")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: lastlogin
        x: 290
        y: 500
        width: 133
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: positive_tag
        x: 502
        y: 307
        width: 93
        height: 20
        text: qsTr("Positive: ")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: positive
        x: 616
        y: 307
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: negative_tag
        x: 502
        y: 335
        width: 93
        height: 20
        text: qsTr("Negative: ")
        wrapMode: Text.NoWrap
        font.pixelSize: 15
    }

    Label {
        id: negative
        x: 616
        y: 335
        width: 152
        height: 20
        text: qsTr("Text")
        font.pixelSize: 15
    }

    Label {
        id: reviews_tag
        x: 502
        y: 253
        text: qsTr("Reviews:")
        font.bold: true
        font.pixelSize: 17
    }
}



