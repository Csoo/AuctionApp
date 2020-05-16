import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: profile
    x: 0
    y: 0
    width: 1080
    height: 690
    visible: false

    property int profileId: 1

    Component.onCompleted: {
        myProfile.getOwnProfile(profile.profileId)
        if (profile.profileId === main.loggedinProfileId) {
            username.text = myProfile.userName
            fullname.text = myProfile.name
            email.text = myProfile.email
            address.text = myProfile.address
            phone.text = myProfile.phone
            createtime.text = myProfile.regDate
        } else {
            username.text = myProfile.userName
            fullname.text = myProfile.name
            createtime.text = myProfile.regDate
        }
        address.visible = profile.profileId === main.loggedinProfileId
        address_tag.visible = profile.profileId === main.loggedinProfileId
        username.visible = profile.profileId === main.loggedinProfileId
        username_tag.visible = profile.profileId === main.loggedinProfileId
        fullname.visible = profile.profileId === main.loggedinProfileId
        fullname_tag.visible = profile.profileId === main.loggedinProfileId
        createtime.visible = profile.profileId === main.loggedinProfileId
        createtime_tag.visible = profile.profileId === main.loggedinProfileId
        phone.visible = profile.profileId === main.loggedinProfileId
        phone_tag.visible = profile.profileId === main.loggedinProfileId
        email.visible = profile.profileId === main.loggedinProfileId
        email_tag.visible = profile.profileId === main.loggedinProfileId
        lastlogin.visible = profile.profileId !== main.loggedinProfileId
        lastlogin_tag.visible = profile.profileId !== main.loggedinProfileId

        profile.visible = true
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Profile")
    }

    Item {
        width: 812
        height: 446
        anchors.verticalCenterOffset: -72
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Label {
            id: username_tag
            x: 144
            y: 201
            width: 93
            height: 20
            text: qsTr("Username: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: username
            x: 258
            y: 201
            width: 152
            height: 20
            text: ""
            font.pixelSize: 15
        }

        Label {
            id: fullname_tag
            x: 144
            y: 229
            width: 93
            height: 20
            text: qsTr("Full Name:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: fullname
            x: 258
            y: 229
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: email_tag
            x: 144
            y: 255
            width: 93
            height: 20
            text: qsTr("E-mail:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: email
            x: 258
            y: 255
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: createtime_tag
            x: 144
            y: 368
            width: 140
            height: 20
            text: qsTr("Account created at: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: createtime
            x: 316
            y: 368
            width: 133
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: address_tag
            x: 144
            y: 281
            width: 93
            height: 20
            text: qsTr("Address:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: address
            x: 258
            y: 281
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: phone_tag
            x: 144
            y: 307
            width: 93
            height: 20
            text: qsTr("Phone:")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: phone
            x: 258
            y: 307
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: lastlogin_tag
            x: 144
            y: 394
            width: 140
            height: 20
            text: qsTr("Last login: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: lastlogin
            x: 316
            y: 394
            width: 133
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: positive_tag
            x: 570
            y: 255
            width: 93
            height: 20
            text: qsTr("Positive: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: positive
            x: 684
            y: 255
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: negative_tag
            x: 570
            y: 283
            width: 93
            height: 20
            text: qsTr("Negative: ")
            wrapMode: Text.NoWrap
            font.pixelSize: 15
        }

        Label {
            id: negative
            x: 684
            y: 283
            width: 152
            height: 20
            text: qsTr("Text")
            font.pixelSize: 15
        }

        Label {
            id: reviews_tag
            x: 570
            y: 201
            text: qsTr("Reviews:")
            font.bold: true
            font.pixelSize: 17
        }
    }
}

