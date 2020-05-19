import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: auctionView
    property int auctionId: 1

    signal userClicked(int userId)

    Component.onCompleted: {
        auctionView.load()
        auctionView.dateCheck()
    }

    function dateCheck() {
        var endDate = new Date(auctionItem.endDate);
        var currentDate = new Date();

        console.log(endDate);
        console.log(currentDate);

        if (endDate < currentDate) {
            bidButton.visible = false;
            bid.visible = false;
            label8.visible = false;
            label10.text = "Winner: ";
        }
    }

    function load() {
        auctionItem.getAuction(auctionId);
        title.title = auctionItem.title
        desc.text = auctionItem.descriptionText
        condition.text = auctionItem.conditionText
        itemColor.text = auctionItem.color
        startDate.text = auctionItem.startDate
        endDate.text = auctionItem.endDate
        price.currentPrice = auctionItem.currentPrice
        bid.placeholderText = "min. " + auctionItem.minStep
        latestUser.userId = auctionItem.lastLicitUserId
        latestUser.text = latestUser.userId !== -1 ? auctionItem.lastLicitUserName : "Nobody bidded."
        owner.text = auctionItem.ownerUserName
        owner.userId = auctionItem.ownerUserId
        swipe.imageCount = auctionItem.getImageCount()
        image1.source = "data:image/jpg;base64," + auctionItem.getImage(0)
        image2.source = "data:image/jpg;base64," + auctionItem.getImage(1)
        image3.source = "data:image/jpg;base64," + auctionItem.getImage(2)
    }

    function bidIsValid() {
        if (main.loggedinProfileId === owner.userId) {
            bidButton.enabled = false
        } else {
            bidButton.enabled = bid.text >= auctionItem.minStep
        }
    }

    function sendBid(auctionId, licitUserId, currentPriceId, bid) {
        main.isLoading = true;
        var result = httpRequest.bidRequest(auctionId, licitUserId, currentPriceId, bid);
        if (result !== auctionItem.currentPrice) {
            auctionView.load()
        } else {
            bidError.open();
        }

        main.isLoading = false;
    }

    Popup {
        id: bidError
        x: parent.width/2-100
        y: parent.height*0.65
        width: 200
        height: 24
        clip: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Text {
            id: bidErrorText
            color: "#dfdfdf"
            text: qsTr("Bid error.")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
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
        width: 252
        height: 397
        anchors.top: frame2.top
        anchors.topMargin: 0
        anchors.left: frame2.right
        anchors.leftMargin: 74

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
                visible: itemColor.text !== "" ? true : false
            }

            Label {
                id: itemColor
                anchors.left: label2.right
                anchors.leftMargin: 40
                visible: itemColor.text !== "" ? true : false
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

        Label {
            id: ownerLabel
            y: 174
            text: qsTr("Auction owner:")
            anchors.left: parent.left
            anchors.leftMargin: 0
            verticalAlignment: Text.AlignTop
            anchors.bottom: element5.top
            anchors.bottomMargin: 20
            color: applicationWindow.highlightTextColor
        }

        Label {
            id: owner
            property int userId: 0
            y: 183
            text: qsTr("Label")
            font.bold: true
            anchors.bottom: ownerLabel.bottom
            anchors.bottomMargin: 0
            anchors.left: ownerLabel.right
            anchors.leftMargin: 12
            opacity: ownerArea.containsMouse ? "0.5" : "1.0"
            MouseArea {
                id: ownerArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: userClicked(owner.userId)
            }
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
        y: -5
        width: 307
        height: 397
        anchors.left: parent.left
        anchors.leftMargin: 141
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 88

        TextField {
            id: bid
            y: 294
            width: 102
            height: 43
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            validator: IntValidator {bottom: 1}
            onTextChanged: auctionView.bidIsValid()
        }

        Label {
            id: label8
            y: 297
            width: 13
            height: 40
            text: qsTr("Ft")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
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
            enabled: false
            onClicked: auctionView.sendBid(auctionId, main.loggedinProfileId, price.currentPrice, bid.text)
        }

        Label {
            id: price
            property int currentPrice: 0
            x: 56
            y: 202
            text: currentPrice + " Ft"
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
                hoverEnabled: latestUser.userId !== -1
                anchors.fill: parent
                onClicked: userClicked(latestUser.userId)
                enabled: latestUser.userId !== -1
            }
        }

        Rectangle {
            height: 236
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 0
            opacity: 0.4
            color: "#343434"
        }

        SwipeView {
            id: swipe
            property int imageCount: 1
            height: 236
            clip: true
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            visible: imageCount > 0
            Image {
                id: image1
                fillMode: Image.PreserveAspectFit
                source: ""
            }
            Image {
                id: image2
                fillMode: Image.PreserveAspectFit
                source: ""
            }
            Image {
                id: image3
                fillMode: Image.PreserveAspectFit
                source: ""
            }
        }
        PageIndicator {
            visible: swipe.imageCount !== 1
            id: indicator
            anchors.bottomMargin: -20
            count: swipe.imageCount
            currentIndex: swipe.currentIndex
            anchors.bottom: swipe.bottom
            anchors.horizontalCenter: swipe.horizontalCenter
        }
        Label {
            visible: swipe.imageCount > 0
            id: next
            text: ">"
            font.bold: true
            font.family: "Courier"
            anchors.bottomMargin: -20
            anchors.bottom: swipe.bottom
            anchors.horizontalCenter: swipe.horizontalCenter
            anchors.horizontalCenterOffset: 50
            opacity: nextArea.containsMouse || swipe.currentIndex === swipe.imageCount - 1 ? 0.5 : 1
            MouseArea {
                anchors.fill: parent
                id: nextArea
                hoverEnabled: true
                enabled: swipe.currentIndex !== swipe.imageCount - 1
                onClicked: swipe.currentIndex = swipe.currentIndex + 1
            }
        }
        Label {
            visible: swipe.imageCount > 0
            id: prev
            text: "<"
            font.bold: true
            font.family: "Courier"
            anchors.bottomMargin: -20
            anchors.bottom: swipe.bottom
            anchors.horizontalCenter: swipe.horizontalCenter
            anchors.horizontalCenterOffset: -50
            opacity: prevArea.containsMouse || swipe.currentIndex === 0 ? 0.5 : 1
            MouseArea {
                anchors.fill: parent
                id: prevArea
                hoverEnabled: true
                enabled: swipe.currentIndex !== 0
                onClicked: swipe.currentIndex = swipe.currentIndex - 1
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_x:312;anchors_y:116}D{i:3;anchors_width:200}
D{i:6;anchors_width:200}D{i:9;anchors_width:279}D{i:19;anchors_height:200;anchors_width:212;anchors_x:66;anchors_y:204}
D{i:22;anchors_x:106}D{i:24;anchors_x:37}D{i:25;anchors_x:112}D{i:26;anchors_x:112;anchors_y:423}
D{i:27;anchors_width:250;anchors_x:"-19";anchors_y:"-11"}D{i:28;anchors_width:250;anchors_x:"-19";anchors_y:"-11"}
D{i:21;anchors_x:106}
}
##^##*/

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
