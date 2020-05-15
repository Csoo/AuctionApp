import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: searchView
    property bool loading: false

    signal auctionClicked(int auctionId)

    function getTags(text) {
        var arr = text.split(",");
        arr.map(s => s.trim());
        return arr;
    }

    function search() {
        searchView.loading = true;
        var tagList = searchView.getTags(tags.text);
        auctionModel.setAuctions(searchBar.text, category.currentText, itemColor.text, condition.currentText, minPrice.text, maxPrice.text, tagList);
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
        Image {
            width: 20
            height: 20
            anchors.verticalCenterOffset: 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: -14
            sourceSize.height: 32
            sourceSize.width: 32
            rotation: 7
            source: "img/search.png"
            anchors.right: parent.right
            opacity: searchArea.containsMouse ? 0.5 : 1
            MouseArea {
                id: searchArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: search()
            }
        }
    }

    BusyIndicator {
        anchors.verticalCenterOffset: 292
        anchors.horizontalCenterOffset: 390
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        running: loading
    }

    ComboBox {
        id: category
        width: 200
        height: 35
        anchors.left: searchBar.left
        anchors.leftMargin: 0
        anchors.top: priceSlider.bottom
        anchors.topMargin: 16
        currentIndex: -1
        displayText: currentIndex == -1 ? "Choose a category..." : currentText
        model: ["Furniture", "Toy", "Tool", "Electronics", "Cars"]
    }
    ComboBox {
        id: condition
        width: 200
        height: 35
        anchors.left: category.right
        anchors.leftMargin: -200
        anchors.top: category.bottom
        anchors.topMargin: 9
        currentIndex: -1
        displayText: currentIndex == -1 ? "Choose a condition..." : currentText
        model: ["new", "used", "bad"]
    }

    TextField {
        id: itemColor
        y: 147
        width: 140
        height: 44
        text: qsTr("")
        anchors.left: condition.right
        anchors.leftMargin: 16
        anchors.verticalCenter: category.verticalCenter
        placeholderText: "Item color"
        horizontalAlignment: Text.AlignLeft
    }

    RangeSlider {
        id: priceSlider
        anchors.horizontalCenter: searchBar.horizontalCenter
        anchors.top: searchBar.bottom
        anchors.topMargin: 8
        width: applicationWindow.width - 340
        height: 35
        snapMode: RangeSlider.SnapAlways
        stepSize: 1000
        to: 100000
        second.value: 10000
        first.value: 1000
    }

    Label {
        id: minPrice
        anchors.verticalCenter: priceSlider.verticalCenter
        anchors.left: searchBar.left
        width: 60
        text: priceSlider.first.value.toFixed(0) + " Ft"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        id: maxPrice
        anchors.verticalCenter: priceSlider.verticalCenter
        anchors.right: searchBar.right
        width: 60
        text: priceSlider.second.value.toFixed(0) == 100000 ? priceSlider.second.value.toFixed(0) + "+ Ft" : priceSlider.second.value.toFixed(0) + " Ft"
        verticalAlignment: Text.AlignVCenter
    }

    TextArea {
        id: tags
        width: 200
        height: 85
        clip: true
        wrapMode: Text.WordWrap
        placeholderText: "e.g. plastic, toy, kids"
        anchors.left: itemColor.right
        anchors.leftMargin: 16
        anchors.top: priceSlider.bottom
        anchors.topMargin: 10
    }

    ListView {
        id: auctionList
        width: 600
        height: 340
        boundsBehavior: Flickable.StopAtBounds
        cacheBuffer: 100
        clip: true
        snapMode: ListView.SnapToItem
        anchors.top: parent.top
        anchors.topMargin: 300
        anchors.left: searchBar.left
        anchors.leftMargin: 0
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
                width: parent.width
                spacing: 100
                Rectangle {
                    height: 40; width: 40;
                    color: "blue"
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    Label {
                        id: label
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
    D{i:0;autoSize:true;height:480;width:640}D{i:6;anchors_height:305;anchors_width:275;anchors_x:140;anchors_y:169}
D{i:7;anchors_height:35;anchors_width:275;anchors_x:140;anchors_y:156}D{i:8;anchors_height:35;anchors_x:416;anchors_y:156}
D{i:9;anchors_x:459}D{i:10;anchors_x:459}D{i:13;anchors_height:231}D{i:21;anchors_x:317}
D{i:22;anchors_x:317}D{i:14;anchors_height:231}
}
##^##*/
