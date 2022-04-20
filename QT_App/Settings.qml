import QtQuick 2.0
import QtQuick
import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3


ApplicationWindow{

    visible: true
    width: 640
    height: 480
    title: qsTr("C-Minder")

    header: ToolBar{
        RowLayout{


            ToolButton{

                text: qstr("HomeButton")
                icon.source: "/Resources/Images/homepage.png"
                Text {
                                    text: parent.text
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

            }

       }

    }
}
