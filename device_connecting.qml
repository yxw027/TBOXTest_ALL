import QtQuick 2.0

Item {
    id: plug_in_device
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
        id: device_name
        anchors.left: device.left
        anchors.leftMargin: 200
        anchors.top: device.top
        anchors.topMargin: 90
        font.pixelSize: 28
        color: "white"
        text: qsTr("设备正在连接中...")
        font.family: fontFamily;
    }
}
