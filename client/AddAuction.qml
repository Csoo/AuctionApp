import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQml 2.12
import QtQuick.Dialogs 1.3

Item {
    id: addAuction

    property date endDate: currentDate

    function setEndDate(days) {
        var endDate = new Date();
        endDate.setDate(endDate.getDate() + (days*1));
        endDate.setHours(endDateHour.value-1);
        if (endDate <= currentDate) { //TODO: min duration
            endDateLabel.color = "red";
            createButton.enabled = false;
        } else {
            endDateLabel.color = applicationWindow.highlightTextColor;
            addAuction.auctionIsValid()
        }
        console.log(endDate.toLocaleString());
        return endDate;
    }

    function auctionIsValid() {
        if (name.text.length == 0 || desctiption.text.length == 0 || price.text.length == 0 || bid.text.length == 0 || category.currentIndex == -1 || condition.currentIndex == -1 || endDateTextField.length == 0) {
            createButton.enabled = false;
        } else {
            createButton.enabled = true;
        }
    }

    function getTags(text) {
        var arr = text.split(",");
        arr.map(s => s.trim());
        return arr;
    }

    function createAuction(userId, title, description, color, price, bid, category, condition, endDate) {
        main.isLoading = true;
        httpRequest.addAuctionRequest(userId, title, description, color, price, bid, category, condition, getTags(tags.text), endDate);
        main.isLoading = false;
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log(fileDialog.fileUrl)
            images.addImage(fileDialog.fileUrl)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    Button {
        id: imageButton
        text: qsTr("Upload Image")
        height: createButton.height
        anchors.left: column.left
        anchors.leftMargin: 0
        anchors.top: createButton.top
        anchors.topMargin: 0
        onClicked: fileDialog.open()
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Add New Auction")
    }

    Button {
        id: createButton
        x: 482
        width: 158
        height: 41
        text: qsTr("Create Auction")
        anchors.right: column1.right
        anchors.rightMargin: 0
        anchors.top: column1.bottom
        anchors.topMargin: 27
        highlighted: true
        enabled: false
        onClicked: addAuction.createAuction(main.loggedinProfileId, name.text, desctiption.text, itemColor.color, price.text, bid.text, category.currentIndex, condition.currentIndex, endDate)
    }

    Item {
        id: column
        y: 8
        width: 295
        height: 344
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 128
        anchors.left: parent.left
        anchors.leftMargin: 148

        Item {
            id: row
            height: 40
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Label {
                id: label
                width: 82
                height: 30
                text: qsTr("Name")
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: name
                height: 44
                text: qsTr("")
                placeholderText: "Item name"
                anchors.right: parent.right
                anchors.rightMargin: 0
                horizontalAlignment: Text.AlignLeft
                onTextEdited: addAuction.auctionIsValid()
            }
        }

        Item {
            id: row2
            height: 130
            anchors.top: row.bottom
            anchors.topMargin: 16
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            TextArea {
                id: desctiption
                width: 200
                height: 120
                text: qsTr("")
                placeholderText: "Item description"
                wrapMode: Text.WordWrap
                anchors.right: parent.right
                anchors.rightMargin: 0
                onTextChanged: addAuction.auctionIsValid()
            }

            Label {
                id: label2
                width: 82
                height: 30
                text: qsTr("Description")
                verticalAlignment: Text.AlignVCenter
            }

        }

        Item {
            id: row3
            height: 40
            anchors.top: row2.bottom
            anchors.topMargin: 16
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            Label {
                id: label3
                width: 82
                height: 30
                text: qsTr("Color (optional)")
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: itemColor
                height: 44
                text: qsTr("")
                anchors.rightMargin: 0
                placeholderText: "Item color"
                anchors.right: parent.right
                horizontalAlignment: Text.AlignLeft
            }
        }

        Item {
            id: row4
            height: 40
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 16
            Label {
                id: label4
                width: 82
                height: 30
                text: qsTr("Starting Price")
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: price
                width: 120
                height: 44
                text: qsTr("")
                anchors.rightMargin: 0
                placeholderText: "$"
                inputMethodHints :Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 1}
                anchors.right: parent.right
                horizontalAlignment: Text.AlignLeft
                onTextEdited: addAuction.auctionIsValid()
            }
            anchors.top: row3.bottom
        }

        Item {
            id: row5
            height: 40
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 0
            Label {
                id: label5
                width: 82
                height: 30
                text: qsTr("Bidding Step")
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: bid
                width: 120
                height: 44
                text: qsTr("")
                inputMethodHints :Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 1}
                anchors.rightMargin: 0
                placeholderText: "$"
                anchors.right: parent.right
                horizontalAlignment: Text.AlignLeft
                onTextEdited: addAuction.auctionIsValid()
            }
            anchors.top: row4.bottom
        }
    }

    Item {
        id: column1
        width: 295
        height: 344
        anchors.left: column.right
        anchors.leftMargin: 50
        anchors.top: column.top
        anchors.topMargin: 0

        Item {
            id: row6
            height: 40
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            ComboBox {
                id: category
                width: 200
                height: 35
                currentIndex: -1
                displayText: currentIndex == -1 ? "Choose category..." : currentText
                anchors.right: parent.right
                anchors.rightMargin: 0
                model: ["Car", "Furniture", "Electronics", "Book", "Toy", "Tool"]
                onCurrentIndexChanged: addAuction.auctionIsValid()
            }

            Label {
                id: label6
                width: 82
                height: 30
                text: qsTr("Category")
                verticalAlignment: Text.AlignVCenter
            }

        }

        Item {
            id: row7
            height: 40
            anchors.top: row6.bottom
            anchors.topMargin: 16
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            ComboBox {
                id: condition
                width: 200
                height: 35
                currentIndex: -1
                displayText: currentIndex == -1 ? "Choose condition..." : currentText
                anchors.rightMargin: 0
                anchors.right: parent.right
                model: ["new", "used", "bad"]
                onCurrentIndexChanged: addAuction.auctionIsValid()
            }

            Label {
                id: label7
                width: 82
                height: 30
                text: qsTr("Condition")
                verticalAlignment: Text.AlignVCenter
            }
        }

        Item {
            id: row8
            height: 70
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 16
            Label {
                id: label8
                width: 82
                height: 30
                text: qsTr("Additional Tags (optional)")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
            }

            TextArea {
                id: tags
                width: 200
                height: 60
                text: qsTr("")
                clip: true
                wrapMode: Text.WordWrap
                placeholderText: "e.g. plastic, toy, kids"
                anchors.right: parent.right
                anchors.rightMargin: 0
            }
            anchors.top: row7.bottom
        }

        Item {
            id: row9
            height: 40
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 16
            TextField {
                id: endDateTextField
                width: 200
                height: 26
                anchors.right: parent.right
                anchors.rightMargin: 0
                bottomPadding: 0
                topPadding: 0
                font.bold: false
                placeholderText: "days"
                inputMethodHints :Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 1; top: 99}
                onTextChanged: addAuction.endDate=setEndDate(endDateTextField.text)
                onTextEdited: addAuction.auctionIsValid()
            }

            Label {
                id: label9
                width: 82
                height: 30
                text: qsTr("Auction Duration")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
            }

            anchors.top: row8.bottom
        }

        Item {
            id: row10
            height: 40
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 20

            SpinBox {
                id: endDateHour
                width: 80
                height: 30
                editable: true
                anchors.right: parent.right
                anchors.rightMargin: 120
                to: 23
                onValueChanged: addAuction.endDate=setEndDate(endDateTextField.text)
            }

            Label {
                id: label10
                width: 82
                height: 30
                text: qsTr("Ending Hour")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
            }

            anchors.top: row9.bottom
        }

        Item {
            id: row11
            height: 40
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.topMargin: 0
            Label {
                id: endDateLabel
                height: 60
                text: qsTr("The auction will end at ") + addAuction.endDate.toLocaleString(Qt.locale(), "yyyy.MM.dd. hh:00") + "."
                anchors.right: parent.right
                color: applicationWindow.highlightTextColor
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                verticalAlignment: Text.AlignVCenter
                font.bold: false
                horizontalAlignment: Text.AlignLeft
            }

            anchors.top: row10.bottom
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_x:32;anchors_y:440}D{i:5;anchors_height:344;anchors_x:20;anchors_y:40}
D{i:23;anchors_height:344;anchors_y:40}
}
##^##*/
