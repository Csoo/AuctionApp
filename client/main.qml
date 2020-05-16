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
        property bool isLoggedIn: false
        property int pageIndex: 0
        property int searchIndex: 0
        property bool isLoading: false

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

            Component {
                id: loggedIn

                SwipeView {
                    id: loggedInSwipeView
                    interactive: false
                    orientation: Qt.Vertical
                    currentIndex: main.pageIndex
                    ProfileView {
                        id: profileView
                        profileId: main.loggedinProfileId
                    }

                    AddAuction {
                        id: addAuction
                    }

                    Item {
                        id: browser
                        Page{
                            visible: main.searchIndex === 0
                            SearchView {
                                id: searchView
                                onAuctionClicked: {
                                    main.searchIndex = 1
                                    auction.auctionId = auctionId
                                }
                            }
                        }
                        Page {
                            visible: main.searchIndex === 1
                            Auction {
                                id: auction
                            }

                        }
                        Page {
                            visible: main.searchIndex === 2

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






