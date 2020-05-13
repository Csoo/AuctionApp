import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: element

    property string title: ""
    height: 110

    Label {
        id: titleLabel
        width: 470
        height: 77
        text: title
        anchors.top: parent.top
        anchors.topMargin: 7
        anchors.left: parent.left
        anchors.leftMargin: 140
        font.bold: true
        padding: 10
        rightPadding: 10
        font.pointSize: 20
        verticalAlignment: Text.AlignBottom
    }


    ToolSeparator {
        id: toolSeparator
        width: applicationWindow.width-200
        anchors.left: parent.left
        anchors.leftMargin: 140
        anchors.top: titleLabel.bottom
        anchors.topMargin: -10
        orientation: Qt.Horizontal
    }
}
