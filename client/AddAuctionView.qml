import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.3

Item {
    FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home
            onAccepted: {
                console.log(fileDialog.fileUrl)
                images.addImage(fileDialog.fileUrl)
            }
            onRejected: {
                console.log("Canceled")
            }
        }
        Button {
            id: button
            x: 288
            y: 220
            text: qsTr("Upload Image")
            onClicked: fileDialog.open()
        }
}


