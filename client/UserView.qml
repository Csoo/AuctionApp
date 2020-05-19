import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: element
    property int rateId: 0

    function sendRating() {
        httpRequest.rateUserRequest()
    }

    function wordfilter(str){
        var fs = require('fs');
        var words = fs.readFileSync('words.txt').toString().split("\r\n");
        var isInclude = words.some(word => str.includes(word));
        return isInclude;
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Rate User")
    }

    TextInput {
        id: textInput
        y: 184
        width: 336
        height: 112
        text: qsTr("Text Input")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 184
        anchors.left: parent.left
        anchors.leftMargin: 152
        font.pixelSize: 12
    }

    Button {
        id: button
        x: 390
        text: qsTr("Send")
        highlighted: true
        anchors.top: textInput.bottom
        anchors.topMargin: 20
        anchors.right: textInput.right
        anchors.rightMargin: 0
        onClicked: sendRating()
    }

    Switch {
        id: isPositive
        x: 213
        text: qsTr("")
        anchors.top: textInput.bottom
        anchors.topMargin: 20
        checked: true
        display: AbstractButton.IconOnly
    }

    Label {
        id: label
        y: 337
        text: qsTr("Positive")
        anchors.verticalCenter: isPositive.verticalCenter
        anchors.left: isPositive.right
        anchors.leftMargin: 10
        color: isPositive.checked ? "44ff22" : ""
    }

    Label {
        id: label1
        x: 181
        y: 330
        text: qsTr("Negative")
        anchors.verticalCenterOffset: 0
        anchors.right: isPositive.left
        anchors.rightMargin: 10
        anchors.verticalCenter: isPositive.verticalCenter
        color: isPositive.checked ? "" : "#aa4422"
    }
}
