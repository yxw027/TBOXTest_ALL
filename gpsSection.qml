import QtQuick 2.0

Item {
    id: gpsSection
    anchors.left: parent.left
    anchors.top: parent.top

    property string text_num: "";

    Image {
        id: gpsFrame
        height: 345
        width: 316
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 230
        anchors.leftMargin: 678
        source: "./image/mainPage/GPSFrame.png"
    }
    
    Image {
        id: gpsBg_1
        width: 289
        height: 242
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 245
        anchors.leftMargin: 696
        source: "./image/mainPage/GPS_bg.png"
    }
    
    Image {
        id: gpsBg_2
        anchors.top: gpsBg_1.bottom
        anchors.left: gpsBg_1.left
        source: "./image/mainPage/GPS_num.png"
    }
    
    Item {
        id: other_signal_section
        anchors.left: parent.left
        anchors.top: parent.top

        Image {
            id: cmcc_sig0
            visible: true
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_0.png"
        }

        Image {
            id: cmcc_sig1
            visible: false
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_1.png"
        }

        Image {
            id: cmcc_sig2
            visible: false
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_2.png"
        }

        Image {
            id: cmcc_sig3
            visible: false
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_3.png"
        }

        Image {
            id: cmcc_sig4
            visible: false
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_4.png"
        }

        Image {
            id: cmcc_sig5
            visible: false
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 711
            source: "./image/gps_sig/sig_4.png"
        }

        Image {
            id: cmcc
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 751
            source: "./image/gps_sig/CMCC.png"
        }

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 512
            anchors.leftMargin: 843
            font.pixelSize: 24
            text: qsTr("4G")
            color: "#f6fcf7"
            font.family: fontFamily;
            //opacity: 0.4
        }

//        Image {
//            id: _2G
//            anchors.top: parent.top
//            anchors.left: parent.left
//            anchors.topMargin: 518
//            anchors.leftMargin: 843
//            source: "./image/gps_sig/_2G_n.png"
//        }

        Image {
            id: _BT
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 514
            anchors.leftMargin: 901
            source: "./image/gps_sig/bt_n.png"
        }

        Image {
            id: _WIFI
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 516
            anchors.leftMargin: 946
            source: "./image/gps_sig/wifi_n.png"
        }
    }

    Text {
        id: text1_name
        color:  "#FFFFFF";
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 714
        anchors.topMargin: 264
        font.pixelSize: 14
        text: qsTr("收星数")
        font.family: fontFamily;
    }

    Text {
        id: text2_num
        color:  "#FFFFFF";
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 714
        anchors.topMargin: 284
        font.pixelSize: 24
        text: text_num
        font.family: fontFamily;
    }

    Loader{
        id: gpsSinal
        width: gpsBg_1.width
        height: gpsBg_1.height
        anchors.fill: gpsBg_1
        source: "./BarGraphArea.qml"
    }

    Image {
        id: _cutline1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 512
        anchors.leftMargin: 827
        source: "./image/gps_sig/_cut_line.png"
    }

    Image {
        id: _cutline2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 512
        anchors.leftMargin: 883
        source: "./image/gps_sig/_cut_line.png"
    }

    Image {
        id: _cutline3
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 512
        anchors.leftMargin: 930
        source: "./image/gps_sig/_cut_line.png"
    }

    Image {
        id: _gps_cut_line0
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 323
        anchors.leftMargin: 714
        source: "./image/gps_sig/gps_cut_line.png"
    }

    Image {
        id: _gps_cut_line1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 363
        anchors.leftMargin: 714
        source: "./image/gps_sig/gps_cut_line.png"
    }

    Image {
        id: _gps_cut_line2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 403
        anchors.leftMargin: 714
        source: "./image/gps_sig/gps_cut_line.png"
    }

    Image {
        id: _gps_cut_line3
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 443
        anchors.leftMargin: 714
        source: "./image/gps_sig/gps_cut_line.png"
    }

    Connections{
        target: Thread
        onSignal_strength:{
            cmcc_sig0.visible = false;
            if(strength<=10)
            {
                cmcc_sig0.visible = true;
            }
            if( (10<strength) && (strength<=30) )
            {
                cmcc_sig1.visible = true;
            }
            if( (30<strength) && (strength<=50) )
            {
                cmcc_sig2.visible = true;
            }
            if( (50<strength) && (strength<=70) )
            {
                cmcc_sig3.visible = true;
            }
            if( (70<strength) && (strength<=100) )
            {
                cmcc_sig4.visible = true;
            }
        }
        onGps_start_num:{
            text_num = num;
        }
        onShow_wifi:{
            //console.log("onShow_wifi is emit!!!");
            _WIFI.source="";
            _WIFI.source="./image/gps_sig/wifi_y.png";
        }
    }

}
