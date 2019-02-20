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
        anchors.centerIn: device
        font.pixelSize: 28
        color: "white"
        text: qsTr("设备连接失败")
        font.family: fontFamily;
    }

    Connections{
        target: Thread
        onDevice_disconnect:{
            //console.log("onDevice_disconnect is emit!!!");
            plug_in_device.visible = true;
        }
    }
}
