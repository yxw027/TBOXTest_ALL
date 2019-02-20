import QtQuick 2.0

Item {
    id: u_disk
    anchors.fill: parent

    Image {
        id: bg
        anchors.fill: parent
        source: "./image/mainPage/bg.png"
    }
    Image {
        id: device
        anchors.centerIn: parent
        source: "./image/u_disk/u_disk_disconn.png"
    }
    Text {
        id: device_name
        anchors.centerIn: device
        font.pixelSize: 28
        color: "white"
        text: qsTr("连接u盘失败")
        font.family: fontFamily;
    }
}
