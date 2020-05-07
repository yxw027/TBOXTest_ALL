import QtQuick 2.0
import QtQuick.Window 2.2

Item {
    id: window
    width: 1024; height: 600;
    
    Rectangle {
        id:testItem
        width: parent.width;
        height: parent.height
        anchors.left: parent.left;
        anchors.top: parent.top
        opacity: 0.9

        Loader{
            id: main_page
            anchors.fill: parent
            source: "./mainpage.qml"
            visible: true
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
        id: errorTip_page
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
            version_page.visible = false;
            errorTip_page.visible = true;
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

    Loader{//delete
        id: version_page
        anchors.fill: parent
        visible: false
        source: "./versionPage.qml"
    }

    Loader{//delete
        id: upgrade
        visible: true
        anchors.centerIn: parent
        source: "upgrade.qml"
    }

    Connections{
        target: Thread
        onDevice_disconnect:{
            console.log("qml:device disconnect");
            Thread.disable_12V();
            if(!errorTip_page.visible)
            {
//                device_diccon.visible = true;
                udisk_diccon.visible = false;
                testItem.opacity = 0.9;
                device_connecting_.visible = false;
                bg.visible = true;
                bg.opacity = 0.8;
            }
        }
        onUdisk_disconnect:{
            console.log("qml:udisk disconnect");
            Thread.disable_12V();
            if(!errorTip_page.visible)
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
                    console.log("++++++");
                    version_page.visible = true;
                }
            }
        }
        onQrcode: {
            qrcode.visible=true;
            version_page.visible = false;
        }
    }
}




