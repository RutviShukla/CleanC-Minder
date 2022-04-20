import QtQuick
import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQml 2.3



ApplicationWindow{
    visible: true
    width: 640
    height: 480
    title: "C-Minder"

    Material.accent: "#000000"
    Material.primary: "#ffb6c1"
    Material.background: "#000000"

    flags: Qt.WindowStaysOnTopHint

    header: ToolBar{
        height: 70

        Rectangle {
            width: 50
            height: 50
            Image {
                width: 50
                height: 50
                source: "/Resources/Images/Logo.png"
            }
        }

        RowLayout{
            anchors.right: parent.right
            height: 70

            ToolButton{
                icon.source: "/Resources/Images/home.png"
                Text {
                              text: "Home"
                              anchors.bottom: parent.bottom
                              anchors.horizontalCenter: parent.horizontalCenter
                     }
            onClicked: {
                homesearch.visible = true
                hometitle.visible = true
                homeview.visible = true
                //settingsview.visible = false
                courseDisp.visible = false
                checkBoxCourses.visible = false
            }
            }

            ToolButton{
                icon.source: "/Resources/Images/TestCopy.png"
                Text {
                        text: "Settings"
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                      }
            onClicked: {
                homesearch.visible = false
                hometitle.visible = false
                homeview.visible = false
                //settingsview.visible = true
                courseDisp.visible = true
                checkBoxCourses.visible = true
            }
            }

            ToolButton{
                icon.source: "/Resources/Images/sync.png"
                Text {
                              text: "Sync"
                              anchors.bottom: parent.bottom
                              anchors.horizontalCenter: parent.horizontalCenter
                     }
            onClicked: {

            }
            }


        Item { Layout.fillWidth: true }
        Switch {
                    checked: true
                    text: qsTr("Change-view")
               }

        }
      }//toolbar

    //Display List View
    ColumnLayout {
     id: mainLayout
     anchors.fill: parent

    Rectangle{
        id: homesearch
     color: "#FFF"
     Layout.fillWidth: true
     height: 40
     z: 2
     RowLayout {
     id: rowLayout
     anchors.fill: parent
     anchors.centerIn: parent
     TextField {
     placeholderText: "Search for assingment here.."
     Layout.fillWidth: true
     font.pointSize: 12
     background: Rectangle {
     implicitWidth: 100
     implicitHeight: 30
     }

     onTextChanged: {
     filterModel.setFilterString(text);
     }
     }
     }
     }


    Rectangle {
        id: hometitle
        Rectangle {
            height: 10
        }
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            text: "Assingments To Do:"
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffb6c1"
            font.pointSize: 25
        }
        Rectangle {
            height: 10
        }
    }

    ListView {
     id: homeview
     model: filterModel
     Layout.minimumHeight: 25
     Layout.fillHeight: true
     Layout.fillWidth: true
     cacheBuffer: 100
     spacing: 10

    delegate: Rectangle{
     width: parent.width - 30
     radius: 50
     //anchors.horizontalCenter: parent.horizontalCenter
     anchors.left: parent.left
     anchors.leftMargin: 5

     height: 45
     color: Qt.lighter("#ffb6c1", 0.8)
     Text {
     id: nameTxt
     text:course + "  |  " + assingment + "  |  " + dueDate    //Use these key words as variables to place them. You can create separate rectangles if you want to
     font.pointSize: 8
     color: "#000"
     anchors.left: parent.left
     anchors.leftMargin: 20
     anchors.verticalCenter: parent.verticalCenter
     }
     }
     }
/*
    ListView {
     id: settingsview
     visible: false
     model: filterModel
     Layout.minimumHeight: 25
     Layout.fillHeight: true
     Layout.fillWidth: true
     cacheBuffer: 100
     spacing: 10

     Rectangle {
         visible: false
         anchors.horizontalCenter: parent.horizontalCenter
         width: 200
         height: 30

         Text {
             anchors.fill: parent
             text: "Choose courses to display:"
             minimumPixelSize: 2
             fontSizeMode: Text.Fit
             font.pixelSize: 200

         }
     }

    delegate: Rectangle{
     width: parent.width - 30
     radius: 50
     //anchors.horizontalCenter: parent.horizontalCenter
     anchors.left: parent.left
     anchors.leftMargin: 5

     height: 45
     color: Qt.lighter("#ffb6c1", 0.8)
     Text {
     text:assingment + "    " + dueDate    //Use these key words as variables to place them. You can create separate rectangles if you want to
     font.pointSize: 8
     color: "#000"
     anchors.left: parent.left
     anchors.leftMargin: 20
     anchors.verticalCenter: parent.verticalCenter
     CheckBox {
            checked: false
            text: course
            //anchors.centerIn: parent
            //leftPadding: indicator.width
            //Layout.alignment: Qt.AlignRight
        }
     }
     }
     }
     */
    ColumnLayout {
        id: checkBoxCourses
        anchors.fill: parent
        //Layout.fillHeight: true
        //Layout.fillWidth: true
        visible: false
        Rectangle {
            id: courseDisp
            height: 35
            Layout.fillWidth: true
            radius: 75
            color: "grey"
            //Layout.alignment: Qt.AlignHCenter
            Text {
                text: "Choose courses to display:"
                font.pixelSize: 25
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#ffb6c1"
            }
        }

        RowLayout{
        Layout.fillWidth: true
        anchors.horizontalCenter: parent.horizontalCenter
        CheckBox {

            //Layout.alignment: Qt.AlignHCenter
            checked: true
            text: "<font color=\"white\">CEN3031</font>"
        }
        CheckBox {
            checked: true
            text: "<font color=\"white\">EVR2001</font>"
        }
        CheckBox {
            checked: true
            text: "<font color=\"white\">CIS4301</font>"

        }
        CheckBox {
            checked: true
            text: "<font color=\"white\">ECO3203</font>"

        }
        }

        Rectangle {
            id: accessToken
            height: 35
            Layout.fillWidth: true

            color: "grey"
            radius: 75
           //Layout.alignment: Qt.AlignHCenter
            Text {
                text: "Set new access token:"
                minimumPixelSize: 2
                fontSizeMode: Text.Fit
                font.pixelSize: 25
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#ffb6c1"
            }
        }
        Rectangle {
                 anchors.horizontalCenter: parent.horizontalCenter
                 width: parent.width/2
                 height: 35
                 radius:  75
                 RowLayout{
                     anchors.horizontalCenter: parent.horizontalCenter
         TextField {

         placeholderText: "Enter new access token"
         Layout.fillWidth: true
         font.pointSize: 9
         background: Rectangle {
         //anchors.horizontalCenter: parent.horizontalCenter
         width: parent.width
         height: 35
         radius:  75
         }
         }
         Button {
                 text: "Submit"
                 background: Rectangle {
                    radius:  75
                 }

             }
                 }
        }

    }



}


}//applicationwindow

