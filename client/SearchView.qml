import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: searchView

    signal auctionClicked(int auctionId, string title)

    function getTags(text) {
        var arr = text.split(",");
        arr.map(s => s.trim());
        return arr;
    }

    function search() {
        main.isLoading = true;
        var tagList = searchView.getTags(tags.text);
        auctionModel.setAuctions(searchBar.text, category.currentIndex, itemColor.text, condition.currentIndex, priceSlider.first.value, maxPrice.text === "100000+ Ft" ? -1 : priceSlider.second.value, tagList);
        auctionList.model = auctionModel;
        resultCount.text = "Number of results: " + auctionModel.rowCount();
        sortBar.visible = true;
        main.isLoading = false;
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
                onClicked: searchView.search()
            }
        }
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
        model: ["All","Car", "Furniture", "Electronics", "Book", "Toy", "Tool"]
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
        model: ["All","New", "Used", "Bad"]
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
        anchors.right: searchBar.right
        anchors.rightMargin: 0
        anchors.bottom: sortBar.top
        anchors.bottomMargin: 0
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
            }
            Label {
                text: price
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 30
            }
            MouseArea {
                id: hightlightArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: auctionClicked(id, title)
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

    Rectangle {
        id: sortBar
        y: 448
        height: 20
        color: applicationWindow.isDark ? "#444444" : "#cccccc"
        anchors.right: auctionList.right
        anchors.rightMargin: 0
        anchors.left: auctionList.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false
        Label {
            id: resultCount
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: "Sort by: "
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 73
            text: "Price "
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            verticalAlignment: Text.AlignVCenter
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 106
            text: "↑"
            font.bold: true
            font.pointSize: 9
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            opacity: area1.containsMouse ? "0.5" : "1"
            MouseArea {
                id: area1
                hoverEnabled: true
                anchors.topMargin: 0
                anchors.fill: parent
                onClicked: auctionModel.sortBy("price", true)
            }
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 116
            text: "↓"
            font.bold: true
            font.pointSize: 9
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            opacity: area2.containsMouse ? "0.5" : "1"
            MouseArea {
                id: area2
                hoverEnabled: true
                anchors.fill: parent
                onClicked: auctionModel.sortBy("price", false)
            }
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 141
            text: "Title "
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            verticalAlignment: Text.AlignVCenter
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 172
            text: "↑"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            font.bold: true
            font.pointSize: 9
            anchors.topMargin: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            opacity: area3.containsMouse ? "0.5" : "1"
            MouseArea {
                id: area3
                hoverEnabled: true
                anchors.fill: parent
                onClicked: auctionModel.sortBy("title", true)
            }
        }
        Label {
            anchors.left: parent.left
            anchors.leftMargin: 182
            text: "↓"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.bold: true
            font.pointSize: 9
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            opacity: area51.containsMouse ? "0.5" : "1"
            MouseArea {
                id: area51
                hoverEnabled: true
                anchors.fill: parent
                onClicked: auctionModel.sortBy("title", false)
            }
        }

    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:6;anchors_height:305;anchors_width:275;anchors_x:140;anchors_y:169}
D{i:7;anchors_height:35;anchors_width:275;anchors_x:140;anchors_y:156}D{i:8;anchors_height:35;anchors_x:416;anchors_y:156}
D{i:9;anchors_x:459}D{i:10;anchors_x:459}D{i:14;anchors_height:231}D{i:13;anchors_height:340;anchors_width:600}
D{i:28;anchors_y:0}D{i:29;anchors_y:0}D{i:31;anchors_y:0}D{i:33;anchors_y:0}D{i:34;anchors_y:0}
D{i:36;anchors_y:0}D{i:25;anchors_width:200;anchors_x:70}
}
##^##*/
