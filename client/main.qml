import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 800
    height: 600
    minimumWidth: 450
    minimumHeight: 300
    title: qsTr("Auction Application")

    property bool isDark: true
    property color highlightTextColor: isDark ? "#90CAF9" : "#2196F3"
    property date currentDate: new Date()

    Material.theme: isDark ? Material.Dark : Material.Light
    Material.accent: Material.Blue


    Item {
        id: main
        anchors.fill: parent

        property int loggedinProfileId: 1
        property int auctionId: 1
        property bool isLoggedIn: false
        property int pageIndex: 0
        property int searchIndex: 0
        property bool isLoading: false
        property int rateId: 0

        Page {
            anchors.fill: parent
            StackView {
                id: loginStack
                focusPolicy: Qt.TabFocus
                initialItem: loggedOut
                anchors.fill: parent
                function loggingIn() {
                    loginStack.push(loggedIn);
                    main.isLoggedIn = true;
                    main.pageIndex = 0;
                }
                function loggingOut() {
                    loginStack.pop();
                    main.isLoggedIn = false;
                }
            }

            Component {
                id: loggedOut
                Item {
                    id: loggedOutItem
                    property int index: 0
                    Page {
                        anchors.fill: parent
                        visible: loggedOutItem.index === 0
                        LoginForm {
                            id: login
                            anchors.fill: parent
                            onLoginAccepted: loginStack.loggingIn()
                        }
                    }
                    Page {
                        visible: loggedOutItem.index === 1
                        anchors.fill: parent
                        RegistrationForm {
                            id: register
                            anchors.fill: parent
                        }
                    }
                }
            }

            Loader {
                anchors.fill: parent
                id: loader
                sourceComponent: undefined
                asynchronous: true
                visible: status == Loader.Ready
            }
            Component {
                id: rater
                UserView {
                    rateId: main.rateId
                    onSendClicked: {
                        main.loggedinProfileId = main.loggedinProfileId + 1
                        main.loggedinProfileId = main.loggedinProfileId - 1
                        loader.sourceComponent = undefined
                    }
                }
            }
            Rectangle {
                radius: 30
                color: backArea2.containsMouse ? applicationWindow.highlightTextColor : applicationWindow.isDark? "#555555" : "#a1a1a1"
                anchors.right: parent.right
                anchors.rightMargin: 100
                anchors.top: parent.top
                anchors.topMargin: 32
                height: 40
                width: 40
                visible: loader.status !== Loader.Null
                Label {
                    text: "<"
                    font.weight: Font.ExtraBold
                    font.pointSize: 14
                    font.family: "Courier"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                }
                MouseArea {
                    id: backArea2
                    hoverEnabled: true
                    anchors.fill: parent
                    enabled: loader.status !== Loader.Null
                    onClicked: loader.sourceComponent = undefined;
                }
            }

            Component {
                id: loggedIn

                SwipeView {
                    id: loggedInSwipeView
                    interactive: false
                    orientation: Qt.Vertical
                    currentIndex: main.pageIndex
                    onCurrentIndexChanged: loader.sourceComponent = undefined
                    ProfileView {
                        id: profileView
                        profileId: main.loggedinProfileId
                        visible: loader.status === Loader.Null

                        onAuctionClicked:{
                            main.auctionId = auctionId
                            loader.sourceComponent = auctionComponent
                        }
                        onRatingClicked: {
                            main.rateId = ratingId
                            loader.sourceComponent = rater
                        }
                    }

                    AddAuction {
                        id: addAuction
                        visible: loader.status === Loader.Null
                        onAuctionCreated: {
                            main.auctionId = auctionId
                            loader.sourceComponent = auctionComponent
                        }
                    }

                    Item {
                        id: browser
                        Page{
                            anchors.fill: parent
                            visible: main.searchIndex === 0
                            SearchView {
                                anchors.fill: parent
                                id: searchView
                                onAuctionClicked: {
                                    main.auctionId = auctionId
                                    main.searchIndex = 1
                                    auctionLoader.sourceComponent = auctionComponent
                                }
                            }
                        }
                        Page {
                            anchors.fill: parent
                            visible: main.searchIndex === 1
                            Loader {
                                anchors.fill: parent
                                id: auctionLoader
                                sourceComponent: undefined
                                asynchronous: true
                                visible: status == Loader.Ready
                            }
                            Component {
                                id: auctionComponent
                                Auction {
                                    id: auction
                                    auctionId: main.auctionId
                                    onUserClicked: {
                                        searchProfile.profileId = userId
                                        console.log(userId)
                                        main.searchIndex = 2
                                    }
                                    visible: auctionLoader.status != Loader.Null || loader.status != Loader.Null
                                }
                            }
                        }

                        Page {
                            anchors.fill: parent
                            visible: main.searchIndex === 2
                            ProfileView {
                                anchors.fill: parent
                                id: searchProfile
                            }
                        }
                        Rectangle {
                            radius: 30
                            color: backArea.containsMouse ? applicationWindow.highlightTextColor : applicationWindow.isDark? "#555555" : "#a1a1a1"
                            anchors.right: parent.right
                            anchors.rightMargin: 100
                            anchors.top: parent.top
                            anchors.topMargin: 32
                            height: 40
                            width: 40
                            visible: main.searchIndex !== 0 && main.pageIndex === 2
                            Label {
                                text: "<"
                                font.weight: Font.ExtraBold
                                font.pointSize: 14
                                font.family: "Courier"
                                font.bold: true
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                anchors.fill: parent
                            }
                            MouseArea {
                                id: backArea
                                hoverEnabled: true
                                anchors.fill: parent
                                enabled: main.searchIndex !== 0 && main.pageIndex === 2
                                onClicked: {
                                    main.searchIndex = main.searchIndex - 1;
                                    if (main.searchIndex === 0) auctionLoader.sourceComponent = undefined;
                                }
                            }
                        }
                    }

                }
            }
        }

        Image {
            width: 30
            sourceSize.height: 32
            sourceSize.width: 32
            opacity: 0.5
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            fillMode: Image.PreserveAspectFit
            source: applicationWindow.isDark ? "img/sun.png" : "img/moon.png"
            MouseArea {
                anchors.fill: parent
                onClicked: applicationWindow.isDark = !applicationWindow.isDark
            }
        }

        SideBar {
            id: sideBar
            transformOrigin: Item.Left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            onProfilPressed: main.pageIndex = 0
            onAddAuctionPressed: main.pageIndex = 1
            onSearchPressed: {
                main.pageIndex = 2
                main.searchIndex = 0
            }
            onSettingPressed: main.isOption = true
            state: main.isLoggedIn ? "loggedIn" : "loggedOut"
        }

        BusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            running: main.isLoading
        }
    }
}






