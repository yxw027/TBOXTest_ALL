import QtQuick 2.0

Item {
    id: qrcodePage
    anchors.fill: parent
    Loader{
        id: bg
        anchors.fill: parent
        source: "./bgSection.qml"
    }
    Image {
        id: qrFrame
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 94
        anchors.leftMargin: 28
        source: "./image/qrcode/qrFrame.png"
    }
    Image {
        id: qrcode
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 127
        anchors.leftMargin: 64
        height: 406
        width: 406
        //source: "image://qrcode/";
    }

    Connections{
        target: Thread
        onQrcode: {
            qrcode.source = "";
            qrcode.source = "image://qrcode/";
            qrcodePage.visible = true;
            //thread_eixt();
        }
    }

    GridView{
        id: carInfo
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 90
        anchors.leftMargin: 553
        height: 480
        width: 402
        cellHeight: 48
        cellWidth: 402
        model:TableModelQR
        delegate: carInfoDelegate
    }
    Component{
        id: carInfoDelegate
        Item {
            id: wrapper; width: carInfo.cellWidth; height: carInfo.cellHeight;
            Text {
                id: tableName
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 26
                text: qsTr(FilePath+":")
                color: "white"
                font.family: fontFamily;
            }
            Text {
                id: tableInfo
                width: parent.width-60
                font.pixelSize: 26
                anchors.left: tableName.right
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr(FileName)
                wrapMode: Text.WrapAnywhere
                color: "white"
                font.family: fontFamily;
            }
            Image {
                id: cut_line1
                anchors.top: tableInfo.bottom
                source: "./image/qrcode/cut_off.png"
            }
        }
    }
}
