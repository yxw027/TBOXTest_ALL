import QtQuick 2.0

Rectangle {
    id:bar
    color: "transparent";
    property alias barHeight: barFg.height;
    property alias barColor: bar.colorTemp;
    function destoryBarItem(){
        bar.destroy();
    }
    Rectangle{
        id:barFg;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 25
        height: 50;
        color:"transparent";
        clip: true;
        Rectangle{
            id:barBgColor
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            height: bar.height
            color: colorTemp
            /*gradient: Gradient {
                GradientStop {
                    position: 1.50;
                    color: "#db0707";
                }
                GradientStop {
                    position: 0.00;
                    color: "#06be3a";
                }
            }*/
        }
    }
    Text {
        id: num
        anchors.top: barFg.bottom
        anchors.horizontalCenter:  barFg.horizontalCenter
        font.pixelSize: 14
        font.bold: true
        color: "white"
        text: qsTr(index)
        font.family: fontFamily;
    }
    property string  index: "";
    property string colorTemp: "green";
}
