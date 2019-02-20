import QtQuick 2.0

Item {
    id: upgradePage
    visible: false
    anchors.fill: parent
    Image {
        id: bg
        anchors.fill: parent
        source: "./image/mainPage/bg.png"
    }
    Image {
        id: device
        anchors.centerIn: parent
        source: "./image/device/device_connect_fail.png"
    }
    Text {
        id: m_text
        anchors.left: device.left
        anchors.leftMargin: 200
        anchors.top: device.top
        anchors.topMargin: 90
        font.pixelSize: 28
        color: "white"
        text: updateText
         font.family: fontFamily;
    }
    property string updateText: ""

    Connections{
        target: Thread
        onUpgrade:{
            //console.log("ppgrade!!!");
            updateText = text;
            upgradePage.visible = true;
        }
    }
}
