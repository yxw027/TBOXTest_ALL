import QtQuick 2.0
import QtQuick.Window 2.2

Item {
    id: window
    width: 1024; height: 600;
    
    Rectangle {
        id:testItem
        width: parent.width; height: parent.height
        anchors.left: parent.left; anchors.top: parent.top
        opacity: 0.9

        Loader{
            id: main_page
            anchors.fill: parent
            source: "./mainpage.qml"
        }

        Loader{
            id: qrcode
            visible:  false;
            anchors.fill: parent
            source: "./qrCode.qml"
        }
    }
    Image {
        id: bg
        visible: false
        anchors.fill: parent
        source: "./image/mainPage/bg.png"
    }
    Loader{
        id: device_connecting_
        visible: true
        anchors.centerIn: parent
        source: "device_connecting.qml"
    }
    Loader{
        id: tooltip_page
        visible: false
        x:0
        y:0
        //anchors.centerIn: parent
        source: "./tooltip.qml"
        onLoaded: {
            item.show_mainpage.connect(on_show_mainpage)
        }
        function on_show_mainpage()
        {
            testItem.visible = true;
            testItem.opacity = 0.9;
            version_page.visible = false;
            tooltip_page.visible = true;
            udisk_diccon.visible = false;
            device_diccon.visible = false;
            bg.visible = true;
            bg.opacity = 0.8;
        }
    }
    Loader{
        id: device_diccon
        visible:  false
        anchors.centerIn: parent
        source: "./device_disconnect.qml"
    }
    Loader{
        id: udisk_diccon
        anchors.centerIn: parent
        visible: false
        source: "./u_disk_conn_fail.qml"
    }

    Loader{
        id: version_page
        anchors.fill: parent
        visible: false
        source: "./versionPage.qml"
    }

    //UPGRADE//93
    Loader{
        id: upgrade
        visible: true
        anchors.centerIn: parent
        source: "upgrade.qml"
    }
    //UPGRADE

    Connections{
        target: Thread
        onDevice_disconnect:{
            console.log("qml:device disconnect");
            Thread.chang_stop_flag();
            Thread.disable_12V();
            if(!tooltip_page.visible)
            {
                device_diccon.visible = true;
                udisk_diccon.visible = false;
                testItem.opacity = 0.9;
                device_connecting_.visible = false;
                bg.visible = true;
                bg.opacity = 0.8;
            }
        }
        onUdisk_disconnect:{
            console.log("qml:udisk disconnect");
            Thread.chang_stop_flag();
            Thread.disable_12V();
            if(!tooltip_page.visible)
            {
                testItem.visible = true;
                udisk_diccon.visible = true;
                testItem.opacity = 0.9;
                device_connecting_.visible = false;
                device_diccon.visible = false;
                bg.visible = true;
                bg.opacity = 0.8;
            }
        }
        onShow_main_page:{
            testItem.opacity = 1;
            device_connecting_.visible = false;
            device_diccon.visible = false;
            udisk_diccon.visible = false;
            bg.visible = false;
        }
        onM_hardkey:{
            if(msgID==2000)
            {
                if(testItem.visible)
                {
                    //console.log("++++++");
                    version_page.visible = true;
                }
            }
        }
    }

    Connections{// hide version page
        target: Thread
        onQrcode: {
            qrcode.visible=true;
            version_page.visible = false;
        }
    }
}



