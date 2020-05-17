import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: auctionView
    property int auctionId: 1

    signal backPressed()
    signal userClicked(int userId)

    Component.onCompleted: {
        auctionItem.getAuction(auctionId);
        title.title = auctionItem.title
        desc.text = auctionItem.descriptionText
        condition.text = auctionItem.conditionText
        itemColor.text = auctionItem.color
        startDate.text = auctionItem.startDate
        endDate.text = auctionItem.endDate
        price.text = auctionItem.currentPrice + " Ft"
        bid.placeholderText = auctionItem.minStep
        latestUser.text = auctionItem.lastLicitUserName
        latestUser.userId = auctionItem.lastLicitUserId
    }

    Title {
        id: title
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Item {
        id: frame
        x: 312
        y: 116
        width: 279
        height: 313
        anchors.verticalCenterOffset: 24
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 49

        Item {
            id: element2
            height: 28
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Label {
                id: label
                width: 60
                text: qsTr("Condition:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                color: applicationWindow.highlightTextColor
            }

            Label {
                id: condition
                anchors.left: label.right
                anchors.leftMargin: 40
            }
        }

        Item {
            id: element3
            x: -1
            y: 2
            height: 28
            anchors.top: element2.bottom
            anchors.left: parent.left
            Label {
                id: label2
                width: 60
                text: qsTr("Color:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                color: applicationWindow.highlightTextColor
            }

            Label {
                id: itemColor
                anchors.left: label2.right
                anchors.leftMargin: 40
            }
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
        }

        TextEdit {
            id: desc
            height: 62
            text: qsTr("Text Edit")
            wrapMode: Text.WordWrap
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: element3.bottom
            anchors.topMargin: 0
            activeFocusOnPress: false
            readOnly: true
            font.pixelSize: 12
            color: condition.color
        }

        Item {
            id: element4
            x: 7
            y: 10
            height: 28
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            Label {
                id: label4
                width: 60
                text: qsTr("End of bidding:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                color: applicationWindow.highlightTextColor
            }

            Label {
                id: endDate
                text: qsTr("Label")
                anchors.left: label4.right
                anchors.leftMargin: 46
            }
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
        }

        Item {
            id: element5
            x: 15
            y: 8
            height: 28
            anchors.left: parent.left
            anchors.bottomMargin: 0
            Label {
                id: label6
                width: 60
                text: qsTr("Auction created:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                color: applicationWindow.highlightTextColor
            }

            Label {
                id: startDate
                text: qsTr("Label")
                anchors.left: label6.right
                anchors.leftMargin: 46
            }
            anchors.right: parent.right
            anchors.bottom: element4.top
            anchors.leftMargin: 0
            anchors.rightMargin: 0
        }
    }

    Item {
        id: frame2
        width: 231
        anchors.left: parent.left
        anchors.leftMargin: 147
        anchors.top: frame.top
        anchors.topMargin: 0
        anchors.bottom: frame.bottom
        anchors.bottomMargin: 0

        TextField {
            id: bid
            y: 247
            width: 100
            height: 38
            text: qsTr("Text Field")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }

        Label {
            id: label8
            y: 247
            width: 13
            height: 38
            text: qsTr("Ft")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            font.pointSize: 11
            anchors.left: bid.right
            anchors.leftMargin: 2
        }

        Button {
            id: bidButton
            x: 121
            y: 247
            width: 91
            height: 38
            text: qsTr("Bid")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            highlighted: true
        }

        Label {
            id: price
            x: 56
            y: 202
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pointSize: 11
            font.bold: true
            anchors.bottom: bid.top
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Label {
            id: label10
            y: 174
            text: qsTr("Highest bidder:")
            anchors.left: parent.left
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignTop
            anchors.bottom: price.top
            anchors.bottomMargin: 20
            color: applicationWindow.highlightTextColor
        }

        Label {
            id: latestUser
            property int userId: 0
            y: 183
            text: qsTr("Label")
            font.bold: true
            anchors.bottom: label10.bottom
            anchors.bottomMargin: 0
            anchors.left: label10.right
            anchors.leftMargin: 12
            opacity: latestUserArea.containsMouse ? "0.5" : "1.0"
            MouseArea {
                id: latestUserArea
                hoverEnabled: true
                anchors.leftMargin: -93
                anchors.fill: parent
                onClicked: userClicked(latestUser.userId)
            }
        }

        Image {
            id: image
            height: 170
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            fillMode: Image.PreserveAspectFit
            source: "data:image/jpg;base64,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"
        }
    }

    Button {
        id: backButton
        x: 510
        text: qsTr("Button")
        anchors.top: frame.bottom
        anchors.topMargin: 20
        anchors.right: frame.right
        anchors.rightMargin: 0
        onClicked: backPressed()
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_width:200}D{i:6;anchors_width:200}
D{i:9;anchors_width:279}D{i:10;anchors_width:200}D{i:13;anchors_width:200}D{i:18;anchors_x:106}
D{i:21;anchors_x:37}D{i:23;anchors_y:423}D{i:22;anchors_x:112}D{i:24;anchors_width:250;anchors_x:-19;anchors_y:-11}
D{i:16;anchors_height:200;anchors_width:212;anchors_x:66;anchors_y:204}D{i:25;anchors_y:423}
}
##^##*/
