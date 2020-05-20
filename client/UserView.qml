import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: element
    property int rateId: 0

    signal sendClicked()

    function wordfilter(str) {
        var wordsStr = "fasz, buzi, geci, kurva, faszfej, bazdmeg, basszameg, bazeg, baszameg, fuck, shit, faggot, nigger, retard, basz, pöcs, bitch, slut";
        var wordsArray = wordsStr.split(", ");
        var isInclude = wordsArray.some(word => str.includes(word));
        return isInclude;
    }

    function sendRating() {
        if (textArea.text !== "") {
            if (wordfilter(textArea.text) === false) {
                httpRequest.rateUserRequest(element.rateId, isPositive.checked, textArea.text);
                sendClicked();
            } else {
                warning.open();
            }
        } else {
            httpRequest.rateUserRequest(element.rateId, isPositive.checked, textArea.text);
            sendClicked();
        }
    }


    Popup {
        id: warning
        x: parent.width/2-100
        y: parent.height*0.65
        width: 300
        height: 24
        clip: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: Text {
            id: warningText
            color: "#dfdfdf"
            text: qsTr("This is a relaxed environment, do not be offensive.")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Rate User")
    }

    TextArea {
        id: textArea
        y: 184
        width: 336
        height: 200
        text: qsTr("")
        placeholderText: "Your opinion goes here"
        wrapMode: Text.WordWrap
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 184
        anchors.left: parent.left
        anchors.leftMargin: 152
    }

    Label {
        id: label2
        x: 152
        y: 148
        width: 82
        height: 30
        text: qsTr("Description")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 390
        anchors.left: parent.left
        anchors.leftMargin: 152
    }


    Button {
        id: button
        x: 390
        text: qsTr("Send")
        highlighted: true
        anchors.top: textArea.bottom
        anchors.topMargin: 20
        anchors.right: textArea.right
        anchors.rightMargin: 0
        onClicked: sendRating()
    }

    Switch {
        id: isPositive
        x: 213
        text: qsTr("")
        anchors.top: textArea.bottom
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
        color: isPositive.checked ? "#44ff22" : label2.color
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
        color: isPositive.checked ? label2.color : "#aa4422"
    }
}
