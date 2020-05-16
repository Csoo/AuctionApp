import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: element1
    property int auctionId: 1
    property string auctionTitle: "Auction"

    Component.onCompleted: {
        main.isLoading = true
        //auctionItem.getAuction(auctionId)
        main.isLoading = false
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: auctionTitle
    }

    Item {
        id: element
        x: 329
        y: 116
        width: 279
        height: 310
        anchors.verticalCenterOffset: 31
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 146
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: element2
            width: 200
            height: 200
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
