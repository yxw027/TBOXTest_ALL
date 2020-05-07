import QtQuick 2.0

Item {
    id: bgSection
    anchors.left: parent.left;
    anchors.top: parent.top

    property string titleText: ""
    property double  powerText: 0;

    Image {
        id: bg
        anchors.fill: parent
        source: "./image/mainPage/bg.png"
    }

    Image {
        id: title
        anchors.left: parent.left
        anchors.top: parent.top
        source: "./image/mainPage/tiltle.png"
    }

    Text {
        id: title_name
        font.pixelSize: 35
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 470
        anchors.topMargin: 15
        color: "white"
        text: titleText
         font.family: fontFamily;
    }

    Image {
        id: logo
        anchors.left: parent.left
        anchors.top: parent.top
        source: "./image/mainPage/logo.png"
    }

    Image {
        id: battery
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 869
        source: "./image/mainPage/battery.png"
    }

    Text {
        id: power
        font.pixelSize: 22
        anchors.left: battery.right
        anchors.leftMargin: 10
        anchors.verticalCenter: battery.verticalCenter
        color: "white"
        text: qsTr("DC "+ powerText + "V")
        font.family: fontFamily;
    }

    Connections{
        target: Thread
        onPower_signal:{
            if(val==false)
            {
                //console.log("power value is not in assign range!!!");
                battery.source = "./image/mainPage/battery_r.png";
            }
            powerText = power;
        }
        onSetTitleText:{
            titleText = tText;
        }
    }

}
