import QtQuick 2.0

Item {
    id: u_disk
    anchors.fill: parent
    visible: false
    Image {
        id: bg
        anchors.fill: parent
        source: "./image/mainPage/bg.png"
    }
    Image {
        id: device
        anchors.centerIn: parent
        source: "./image/u_disk/plug_in_device.png"
    }
    Text {
        id: device_name
        anchors.centerIn: device
        font.pixelSize: 28
        color: "white"
        text: qsTr("请连接设备")
    }
    Connections{
        target: Thread
        onDevice_disconnect:{
            u_disk.visible = true;
        }
    }
}
