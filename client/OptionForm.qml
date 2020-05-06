import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Item {
    id: option
    property bool dark: darkSwitch.checked ? true : false

    Title {
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("Option")
    }

    Switch {
        id: darkSwitch
        x: 344
        y: 220
        hoverEnabled: false
        checked: true
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
