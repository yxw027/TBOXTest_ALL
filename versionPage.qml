import QtQuick 2.0

Item {
    id: version_page
    anchors.fill: parent
    property string text_num: "";
    property string stime: ""
    property string  mcuVersion: ""
    property string  appVersion: ""
    property string  osVersion: ""
    property string  sysVersion: ""
    
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
        anchors.leftMargin: 50
        anchors.topMargin: 110
        spacing: 16
        
        Rectangle {
            id:rc1
            width: 100; height: item_1.height
            color: "transparent"
            Image { id: item_1; width: 500; source: "./image/versionpage/item_n.png" }
            Text { id: mcu; anchors.left: item_1.left; anchors.leftMargin: 30; anchors.verticalCenter: item_1.verticalCenter; font.pixelSize: 28; color: "white"; text: qsTr("MCU版本:" + mcuVersion) }
        }
        
        Rectangle {
            id:rc2
            width: 100; height: item_2.height
            color: "transparent"
            Image { id: item_2; width: 500; source: "./image/versionpage/item_n.png" }
            Text { id: app; anchors.left: item_2.left; anchors.leftMargin: 30; anchors.verticalCenter: item_2.verticalCenter; font.pixelSize: 28; color: "white"; text: qsTr("APP版本:" + appVersion) }
        }
        
        Rectangle {
            id:rc3
            width: 100; height: 104
            color: "transparent"
            Image { id: item_3; width: 500; source: "./image/versionpage/item_n.png" }
            Text { id: os; anchors.left: item_3.left; anchors.leftMargin: 30; anchors.verticalCenter: item_3.verticalCenter; font.pixelSize: 28; color: "white"; text: qsTr("OS版本:" + osVersion) }
        }
        
        Rectangle {
            id:rc4
            width: 100; height: 104
            color: "transparent"
            Image { id: item_4; width: 500; source: "./image/versionpage/item_n.png" }
            Text { id: sys; anchors.left: item_4.left; anchors.leftMargin: 30; anchors.verticalCenter: item_4.verticalCenter; font.pixelSize: 28; color: "white"; text: qsTr("系统版本:" + sysVersion) }
         }
    }
    
    Item {
        id: gpsSec
        x: 450; y: 200
        width: 500; height: 400
        
        Image {
            id: gpsFrame
            width: 330; height: 330
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.leftMargin: 200
            source: "./image/mainPage/GPSFrame.png"
        }
        
        Image {
            id: gpsBg1
            width: 290; height: 290
            anchors.left: gpsFrame.left
            anchors.top: gpsFrame.top
            anchors.topMargin: 20
            anchors.leftMargin: 20
            source: "./image/mainPage/GPS_bg.png"
        }
        
        Text {
            id: text1name
            color:  "#FFFFFF";
            anchors.left: gpsBg1.left
            anchors.top: gpsBg1.top
            anchors.leftMargin: 10
            anchors.topMargin: 10
            font.pixelSize: 30
            text: qsTr("收星数: ")
            font.family: fontFamily;
        }
    
        Text {
            id: text2num
            color:  "#FFFFFF";
            anchors.left: text1name.right
            anchors.top: text1name.top
            //anchors.leftMargin: 734
            //anchors.topMargin: 284
            font.pixelSize: 30
            text: text_num
            font.family: fontFamily;
        }
        
        Text {
            id: time
            color:  "#FFFFFF";
            anchors.left: text1name.left
            anchors.top: text1name.bottom
            anchors.topMargin: 10
            font.pixelSize: 30
            text: qsTr("启动时间: ")
            font.family: fontFamily;
        }
    
        Text {
            id: sTime
            color:  "#FFFFFF";
            anchors.left: time.right
            anchors.top: time.top
            //anchors.leftMargin: 734
            //anchors.topMargin: 284
            font.pixelSize: 30
            text: stime
            font.family: fontFamily;
        }
        
        Loader{
            id: gpsSignal
            width: gpsBg1.width
            height: gpsBg1.height
            anchors.fill: gpsBg1
            source: "./BarGraphArea.qml"
        }
    }
    
    Connections{
        target: Thread
        onGps_start_num: {
            text_num = num;
        }
    }
    
    Connections {
        target: Thread
        onGps_start_time: {
            stime = time;
        }
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
}
