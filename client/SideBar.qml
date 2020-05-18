import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: sidebar
    width: 55
    opacity: 0.8
    clip: true

    signal profilPressed()
    signal addAuctionPressed()
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
                target: profilArea
                enabled: true
            }
            PropertyChanges {
                target: addAuction
                opacity: 1.0
            }
            PropertyChanges {
                target: addAuctionArea
                enabled: true
            }
            PropertyChanges {
                target: search
                opacity: 1.0
            }
            PropertyChanges {
                target: searchArea
                enabled: true
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
                target: profilArea
                enabled: false
            }
            PropertyChanges {
                target: addAuction
                opacity: 0.0
            }
            PropertyChanges {
                target: addAuctionArea
                enabled: false
            }
            PropertyChanges {
                target: search
                opacity: 0.0
            }
            PropertyChanges {
                target: searchArea
                enabled: false
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
                targets: [profil, addAuction, search, logout]
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
        id: blackBar
        x: 7
        y: 40
        color: "#000000"
        visible: true
        opacity: 0.74
        border.width: 0
        anchors.fill: parent
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: profil.verticalCenter
        height: 40
        width: blackBar.width
        color: main.pageIndex === 0 ? "#444444" : "#317de8"
        opacity: main.isLoggedIn ? 0.4 : 0.0
        visible: profilArea.containsMouse || main.pageIndex === 0 ? true : false
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: search.verticalCenter
        height: 40
        width: blackBar.width
        color: main.pageIndex === 2 ? "#444444" : "#317de8"
        opacity: main.isLoggedIn ? 0.4 : 0.0
        visible: searchArea.containsMouse || main.pageIndex === 2 ? true : false
    }

    Rectangle {
        id: logoutHighlight
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: logout.verticalCenter
        height: 40
        width: blackBar.width
        color: "#317de8"
        opacity: 0.4
        visible: logoutArea.containsMouse && sideBar.state === "loggedIn" ? true : false
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: quit.verticalCenter
        height: 40
        width: blackBar.width
        color: "#317de8"
        opacity: 0.4
        visible: quitArea.containsMouse ? true : false
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: addAuction.verticalCenter
        height: 40
        width: blackBar.width
        color: main.pageIndex === 1 ? "#444444" : "#317de8"
        opacity: main.isLoggedIn ? 0.4 : 0.0
        visible: addAuctionArea.containsMouse || main.pageIndex === 1 ? true : false
    }

    Image {
        id: profil
        x: 0
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
        sourceSize.height: 32
        sourceSize.width: 32
        anchors.top: parent.top
        anchors.topMargin: 42
        fillMode: Image.PreserveAspectFit
        source: "img/profile.png"
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
        antialiasing: true
        sourceSize.height: 32
        sourceSize.width: 32
        anchors.top: addAuction.bottom
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
        id: addAuction
        x: 0
        width: 32
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
        sourceSize.height: 32
        sourceSize.width: 32
        anchors.top: profil.bottom
        anchors.topMargin: 22
        fillMode: Image.PreserveAspectFit
        source: "img/addauction.png"

        MouseArea {
            id: addAuctionArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: sidebar.addAuctionPressed()
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
        antialiasing: true
        sourceSize.height: 32
        sourceSize.width: 32
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
        anchors.horizontalCenterOffset: 0
        anchors.bottom: quit.top
        sourceSize.height: 32
        source: "img/logout.png"
        MouseArea {
            id: logoutArea
            rotation: -90
            hoverEnabled: true
            anchors.fill: parent
            onClicked: loginStack.loggingOut()
        }
        fillMode: Image.PreserveAspectFit
        anchors.bottomMargin: 22
        antialiasing: true
        sourceSize.width: 32
        anchors.horizontalCenter: parent.horizontalCenter
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200}
}
##^##*/
