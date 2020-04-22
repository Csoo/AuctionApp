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

    property bool isDark: settings.dark ? true : false
    property color highlightTextColor: isDark ? "#90CAF9" : "#2196F3"

    Material.theme: isDark ? Material.Dark : Material.Light
    Material.accent: Material.Blue


    Item {
        id: main
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        property bool isOption: false
        property bool isLoggedIn: false
        property int pageIndex: 0

        Page {
            visible: !main.isOption
            anchors.fill: parent
            StackView {
                id: loginStack
                focusPolicy: Qt.TabFocus
                initialItem: loggedOut
                anchors.fill: parent
                function loggingIn() {
                    loginStack.push(loggedIn);
                    main.isLoggedIn = true;
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
                    currentIndex: main.pageIndex
                    ProfileView {
                        id: profileView
                    }

                    AddAuctionView {
                        id: addView
                    }

                }
            }
        }

        Page {
            visible: main.isOption
            anchors.fill: parent
            OptionForm {
                id: settings
            }
            Button {
                x: 374
                y: 378
                text: "Back"
                onClicked: main.isOption = false
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
            onSearchPressed: main.pageIndex = 1
            onSettingPressed: main.isOption = true
            state: main.isLoggedIn ? "loggedIn" : "loggedOut"
        }

    }
}






