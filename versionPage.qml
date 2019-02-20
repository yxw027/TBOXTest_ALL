import QtQuick 2.0

Item {
    id: version_page
    anchors.fill: parent

    Loader{
        id: bgSection
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.fill: parent
        source: "./bgSection.qml"
    }

    Column {
         anchors.left: parent.left
         anchors.top: parent.top
         anchors.leftMargin: 138
         anchors.topMargin: 110
         spacing: 16

         Rectangle {
             id:rc1
             width: item_1.width
             height: item_1.height
             color: "transparent"
             Image { id: item_1; source: "./image/versionpage/item_n.png" }
             Text { id: mcu; anchors.centerIn:item_1; font.pixelSize: 28; color: "white"; text: qsTr("MCU版本:" + mcuVersion) }
         }


         Rectangle {
             id:rc2
             width: item_2.width
             height: item_2.height
             color: "transparent"
             Image { id: item_2; source: "./image/versionpage/item_n.png" }
             Text { id: app; anchors.centerIn: item_2; font.pixelSize: 28; color: "white"; text: qsTr("APP版本:" + appVersion) }
         }

        Rectangle {
            id:rc3
            width: 748
            height: 104
            color: "transparent"
            Image { id: item_3; source: "./image/versionpage/item_n.png" }
            Text { id: os; anchors.centerIn: item_3; font.pixelSize: 28; color: "white"; text: qsTr("OS版本:" + osVersion) }
         }
        /*
        Rectangle {
            id:rc4
            width: 748
            height: 104
            Image { id: item_4; source: "./image/versionpage/item_n.png" }
            Text { id: sys; anchors.centerIn: item_4.Center; font.pixelSize: 28; color: "white"; text: qsTr("系统版本:" + sysVersion) }
         }*/
    }
    
    Connections{
        target: Thread
        onMcuVersion:
        {
            mcuVersion = mcu_buf;
        }
        onAppVersion:
        {
            appVersion = app_buf;
        }
        onOsVersion:
        {
            osVersion = os_buf;
        }
        onSysVersion:
        {
            sysVersion = sys_buf;
        }
    }

    property string  mcuVersion: ""
    property string  appVersion: ""
    property string  osVersion: ""
    property string  sysVersion: ""
}
