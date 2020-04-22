import QtQuick 2.0

Item {
    id: sidebar
    width: 55
    opacity: 0.7
    clip: true

    signal profilPressed()
    signal searchPressed()
    signal settingPressed()

    states: [
        State {
            name: "loggedIn"
            PropertyChanges {
                target: profil
                opacity: 1.0
            }
            PropertyChanges {
                target: search
                opacity: 1.0
            }
            AnchorChanges {
                target: setting
                anchors.top: search.bottom
            }
            PropertyChanges {
                target: logout
                opacity: 1.0
            }
        },
        State {
            name: "loggedOut"
            PropertyChanges {
                target: profil
                opacity: 0.0
            }
            PropertyChanges {
                target: search
                opacity: 0.0
            }
            AnchorChanges {
                target: setting
                anchors.top: parent.top
            }
            PropertyChanges {
                target: logout
                opacity: 0.0
            }
        }
    ]

    transitions: [
        Transition {
            from: "loggedOut"
            to: "loggedIn"
            reversible: true

            NumberAnimation {
                targets: [profil, search, logout]
                properties: "opacity"
                duration: 500
                easing.type: Easing.InOutQuad
            }
            AnchorAnimation {
                duration: 200
            }
        }
    ]

    state: "loggedOut"

    Rectangle {
        id: rectangle
        x: 7
        y: 40
        color: "#000000"
        opacity: 0.8
        border.width: 0
        anchors.fill: parent
    }

    Image {
        id: profil
        opacity: profilArea.containsMouse ? 1.0 : 0.82
        x: 0
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
        sourceSize.height: 88
        sourceSize.width: 88
        anchors.top: parent.top
        anchors.topMargin: 42
        fillMode: Image.PreserveAspectFit
        source: "img/profil.png"
        MouseArea {
            anchors.fill: parent
            id: profilArea
            hoverEnabled: true
            onClicked: sidebar.profilPressed()
        }
    }


    Image {
        id: search
        x: 0
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: searchArea.containsMouse ? 1.0 : 0.82
        antialiasing: true
        sourceSize.height: 88
        sourceSize.width: 88
        anchors.top: profil.bottom
        anchors.topMargin: 22
        fillMode: Image.PreserveAspectFit
        source: "img/search.png"

        MouseArea {
            id: searchArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: sidebar.searchPressed()
        }
    }


    Image {
        id: setting
        x: 0
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: settingArea.containsMouse ? 1.0 : 0.82
        antialiasing: true
        sourceSize.height: 88
        sourceSize.width: 88
        anchors.top: search.bottom
        anchors.topMargin: 22
        fillMode: Image.PreserveAspectFit
        source: "img/setting.png"

        MouseArea {
            id: settingArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: sidebar.settingPressed()
        }
    }

    Image {
        id: quit
        x: 0
        y: 440
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        opacity: quitArea.containsMouse ? 1.0 : 0.82
        antialiasing: true
        sourceSize.height: 88
        sourceSize.width: 88
        fillMode: Image.PreserveAspectFit
        source: "img/exit.png"

        MouseArea {
            id: quitArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: Qt.quit()
        }
    }

    Image {
        id: logout
        x: 6
        y: 393
        width: 32
        height: 32
        rotation: -90
        anchors.horizontalCenterOffset: 0
        anchors.bottom: parent.bottom
        sourceSize.height: 88
        source: "img/exit.png"
        MouseArea {
            id: logoutArea
            rotation: -90
            hoverEnabled: true
            anchors.fill: parent
            onClicked: loginStack.loggingOut()
        }
        fillMode: Image.PreserveAspectFit
        opacity: logoutArea.containsMouse ? 1.0 : 0.82
        anchors.bottomMargin: 55
        antialiasing: true
        sourceSize.width: 88
        anchors.horizontalCenter: parent.horizontalCenter
    }



}

/*##^##
Designer {
    D{i:10;anchors_height:36}D{i:1;anchors_height:200;anchors_width:200}
}
##^##*/
