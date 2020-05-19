import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: profile
    x: 0
    y: 0
    width: 1080
    height: 690

    property int profileId: 0

    signal auctionClicked(int auctionId)
    signal ratingClicked(int ratingId)

    onProfileIdChanged: {
        profile.profileId === main.loggedinProfileId ? myProfile.getOwnProfile(profile.profileId) : myProfile.getOtherProfile(profileId)
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
            lastlogin.text = myProfile.lastDate
        }

        address.visible = profile.profileId === main.loggedinProfileId
        address_tag.visible = profile.profileId === main.loggedinProfileId
        phone.visible = profile.profileId === main.loggedinProfileId
        phone_tag.visible = profile.profileId === main.loggedinProfileId
        email.visible = profile.profileId === main.loggedinProfileId
        email_tag.visible = profile.profileId === main.loggedinProfileId
        lastlogin.visible = profile.profileId !== main.loggedinProfileId
        lastlogin_tag.visible = profile.profileId !== main.loggedinProfileId

        ratingModel.setRatings(profile.profileId)
        ratingModel.rowCount() === 0 ? ratingList.model = noRating : ratingList.model = ratingModel
        ratingModel.rowCount() === 0 ?  positiveLabel.text = "" : positiveLabel.text = myProfile.positive
        ratingModel.rowCount() === 0 ?  negativeLabel.text = "" : negativeLabel.text = myProfile.negative

        pendingModel.setPendings(profile.profileId)
        pendingList.model = pendingModel
    }

    ListModel {
        id: noRating
        ListElement {
            description: "This user has no ratings yet."
            isPositive: -1
            raterId: 0
            raterUsername: ""
            ratingDate: ""
        }
    }

    Title {
        id: title
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Profile")
    }

    Label {
        id: label
        y: 176
        width: 120
        height: 22
        text: qsTr("User ratings")
        font.pointSize: 14
        font.bold: true
        anchors.left: ratingList.left
        anchors.leftMargin: 4
        anchors.bottom: ratingList.top
        anchors.bottomMargin: 6
    }

    Item {
        id: frame
        y: 82
        width: 372
        height: 426
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 182
        anchors.left: parent.left
        anchors.leftMargin: 26
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
    }

    ListView {
        id: ratingList
        x: 822
        y: 0
        width: 258
        clip: true
        spacing: 16
        snapMode: ListView.SnapToItem
        layoutDirection: Qt.LeftToRight
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 218
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        Rectangle {
            color: "#000000"
            anchors.fill: parent
            opacity: 0.2
        }

        delegate: Item {
            x: 5
            width: ratingList.width
            height: message.contentHeight + 60
            Column {
                id: row1
                spacing: 10
                width: parent.width
                height: parent.height

                Label {
                    id: isPositiveLabel
                    text: isPositive === -1 ? "" : isPositive === 1 ? "Positive" : "Negative"
                    leftPadding: 6
                    font.bold: true
                    color: isPositive === 1 ? "#44ff22" : "#aa4422"
                }

                TextEdit {
                    id: message
                    color: rateDate.color
                    text: description
                    textMargin: 6
                    activeFocusOnPress: true
                    readOnly: true
                    font.pointSize: 12
                    width: parent.width - 30
                    height: contentHeight
                    wrapMode: Text.WordWrap
                }
                Row {
                    spacing: 72
                    width: message.width
                    property int userId: raterId
                    Label {
                        width: 50
                        id: raterNameLabel
                        text: raterUsername
                        leftPadding: 6
                        font.pointSize: 8
                    }
                    Label {
                        id: rateDate
                        text: ratingDate
                        font.italic: true
                        font.pointSize: 8
                    }
                }
                ToolSeparator {
                    y: 10
                    width: ratingList.width
                    orientation: Qt.Horizontal
                }
            }
        }
    }

    Label {
        id: positiveLabel
        y: 190
        text: qsTr("Label")
        anchors.verticalCenter: label.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 26
        color: "#44ff22"
    }

    Label {
        id: negativeLabel
        y: 190
        text: qsTr("Label")
        anchors.verticalCenter: positiveLabel.verticalCenter
        anchors.left: positiveLabel.right
        anchors.leftMargin: 12
        color: "#aa4422"
    }

    ListView {
        id: pendingList
        y: 4
        width: 291
        anchors.left: parent.left
        anchors.leftMargin: 161
        anchors.bottom: parent.bottom
        ScrollBar.vertical: ScrollBar {
            active: true
        }
        delegate: Item {
            id: element
            width: pendingList.width
            height: 50
            Column {
                id: row2
                width: parent.width
                height: parent.height
                spacing: 10

                Label {
                    id: userToRate
                    width: 50
                    text: username
                    topPadding: 10
                    leftPadding: 20
                    font.pointSize: 10
                }
                Label {
                    id: wonAuction
                    text: auctionTitle
                    leftPadding: 20
                    font.italic: true
                    font.pointSize: 8
                    opacity: auctionArea.containsMouse ? 0.5 : 1
                    MouseArea {
                        id: auctionArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: profileView.auctionClicked(auctionId)
                    }
                }
            }

            Button {
                id: rateButton
                text: "Rate"
                anchors.verticalCenter: row2.verticalCenter
                anchors.left: row2.right
                anchors.leftMargin: -100
                highlighted: true
                onClicked: profileView.ratingClicked(ratingId)
            }

            ToolSeparator {
                y: 50
                width: pendingList.width
                orientation: Qt.Horizontal
            }
        }
        anchors.top: frame.bottom
        anchors.bottomMargin: 0
        spacing: 16
        snapMode: ListView.SnapToItem
        anchors.topMargin: 40
        layoutDirection: Qt.LeftToRight
        Rectangle {
            color: "#000000"
            anchors.fill: parent
            opacity: 0.2
        }
    }

    Label {
        id: label1
        x: 4
        y: 486
        width: 120
        height: 22
        text: qsTr("Pending ratings")
        anchors.leftMargin: 4
        anchors.bottom: pendingList.top
        anchors.bottomMargin: 6
        font.pointSize: 14
        anchors.left: pendingList.left
        font.bold: true
    }

}


/*##^##
Designer {
    D{i:4;anchors_x:830}D{i:17;anchors_height:160;anchors_y:80}D{i:18;anchors_height:160;anchors_y:80}
D{i:30;anchors_x:998}D{i:31;anchors_x:1037}D{i:41;anchors_x:830}D{i:32;anchors_x:826}
D{i:42;anchors_x:830}
}
##^##*/
