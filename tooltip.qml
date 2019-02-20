import QtQuick 2.0

Item {
    id: tooltip_view

    Image {
        id: title
        height: 74
        width: 514
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 247
        anchors.topMargin: 128
        source: "./image/tooltip/title.png"
    }
    Text {
        id: tipName
        anchors.centerIn: title
        font.pixelSize: 28
        color: "white"
        text: qsTr("测试错误")
        font.family: fontFamily;
    }
    Image {
        id: tooltipFrame
        height: 186
        width: 514
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 247
        anchors.topMargin: 202
        source: "./image/tooltip/bg.png"
    }
    Text {
        id: tipError
        anchors.centerIn: tooltipFrame
        font.pixelSize: 28
        color: "darkgoldenrod"
        text: qsTr(errorName + ":" + errorCode)
        font.family: fontFamily;
    }
    Loader{
        id: bt_left
        width: 516
        height: 74
        clip: true
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 247
        anchors.topMargin: 388
        source: "./Button.qml"
        onLoaded: {
            item.normalSource = "./image/tooltip/restart_n.png";
            item.pressSource = "./image/tooltip/restart_p.png";
            item.centerText = "重新测试";
            item.clicked_m.connect(tooltip_view_false);
        }
        function tooltip_view_false()
        {
            Thread.restart();
            Thread.init();
            tooltip_view.visible = false;
        }
    }
    
    Connections{
        target: Thread//errorCode(QString functionName, int param);
        onErrorCode: {
            show_mainpage();
            errorName = functionName
            errorCode = param;
            tooltip_view.visible = true;
            Thread.chang_stop_flag();
            Thread.disable_12V();
            MainWindow.update_db_flag(false);
            //thread_eixt();
        }
    }

    signal show_mainpage();
    property int errorCode;
    property string errorName: "";
}
