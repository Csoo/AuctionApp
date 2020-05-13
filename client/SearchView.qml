import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: searchView
    property bool loading: false

    signal auctionClicked(int auctionId)

    function search() {
        searchView.loading = true;
        auctionModel.setAuctions();
        auctionList.model = auctionModel;
        console.log(auctionModel.rowCount());
        searchView.loading = false;
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Search Auctions")
    }

    TextField {
        id: searchBar
        x: 140
        y: 116
        width: applicationWindow.width - 220
        color: "#777777"
        placeholderText: "search"
        leftPadding: 20
        bottomPadding: 0
        topPadding: 3
        background: Rectangle { width: searchBar.width+20; height: 28; color: applicationWindow.isDark ? "#1f1f1f" : "#d4d4d4"; radius: 20}
        onAccepted: search()
    }

    BusyIndicator {
        running: loading
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ComboBox {
        id: category
        x: 80
        width: 144
        height: 35
        displayText: ""
        anchors.top: searchBar.bottom
        anchors.topMargin: 24
        currentIndex: -1
        model: ["Furniture", "Toy", "Tool", "Electronics", "Cars"]
    }
    ComboBox {
        id: condition
        x: 245
        y: 156
        width: 119
        height: 35
        anchors.bottom: category.bottom
        anchors.bottomMargin: 0
        currentIndex: -1
        model: ["new", "used", "bad"]
    }

    TextField {
        id: itemColor
        y: 147
        width: 140
        height: 44
        text: qsTr("")
        anchors.left: condition.right
        anchors.leftMargin: 10
        anchors.verticalCenter: category.verticalCenter
        placeholderText: "Item color"
        horizontalAlignment: Text.AlignLeft
    }

    ListView {
        id: auctionList
        width: 681
        height: 231
        clip: true
        snapMode: ListView.NoSnap
        anchors.top: parent.top
        anchors.topMargin: 249
        anchors.left: parent.left
        anchors.leftMargin: 64
        interactive: true
        ScrollBar.vertical: ScrollBar {
            active: true
        }

        delegate: Item {
            id: element
            x: 5
            width: auctionList.width
            height: 70
            Row {
                id: row
                spacing: 100
                Rectangle {
                    height: 40; width: 40;
                    color: "blue"
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    Label {
                        text: title
                        font.bold: true
                    }
                    Label {
                        text: condition
                    }
                }
                Label {
                    text: price
                    anchors.verticalCenter: parent.verticalCenter
                }

            }
            MouseArea {
                id: hightlightArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: auctionClicked(id)
            }
            Rectangle {
                id: hightlight
                anchors.verticalCenter: row.verticalCenter
                height: row.height + 20
                width: auctionList.width
                color: "white"
                visible: hightlightArea.containsMouse ? true : false
                opacity: 0.1
            }
            ToolSeparator {
                y: 42
                width: auctionList.width
                orientation: Qt.Horizontal
            }
        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;anchors_height:305;anchors_width:275;anchors_x:64;anchors_y:169}
D{i:7;anchors_x:416}D{i:8;anchors_x:459}
}
##^##*/
