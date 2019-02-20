import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    id: test_list_section
    anchors.top: parent.top; anchors.left: parent.left
    
    Image {
        id: listframe
        width: 636; height: 360
        anchors { top: parent.top; left: parent.left; topMargin: 230; leftMargin: 24 }
        source: "./image/mainPage/listFrame.png"
    }
    Item {//测试模型
        id: list
        width: 636; height: 360
        anchors { left: listframe.left; top: listframe.top; fill: listframe; }
        clip: true
        PathView{
            id: testList
            anchors { left: parent.left; top: parent.top; fill: parent; }
            model: DataModel
            interactive: false
            delegate: delegate
            path:coverFlowPath
            pathItemCount: 5
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            highlightRangeMode: PathView.StrictlyEnforceRange
        }
        Component{//模型代理器
            id: delegate
            Item {
                id: wrapper;  width: 636; height: 78;  scale:PathView.iconScale; focus: true;
                Image {
                    id: hightlight;  width: 660; height: 116;
                    anchors.verticalCenter: testName.verticalCenter;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.horizontalCenterOffset: 108
                    clip: true
                    source: testList.currentIndex === index ? "./image/mainPage/hightLight.png" :""
                }
                Text { 
                    id: testName; 
                    anchors.left: parent.left; anchors.leftMargin: parent.width/2; 
                    color: "white"; 
                    font.pixelSize: 30; 
                    text: FilePath; 
                    font.family: fontFamily; 
                }
            }
        }
        Path{
            id:coverFlowPath
            startX: list.width/3; startY: 0
            PathAttribute{name:"iconScale";value: 0.8}
            PathLine{x:coverFlowPath.startX; y:list.height/2}
            PathAttribute{name:"iconScale";value: 1.0}
            PathLine{x:coverFlowPath.startX; y:list.height}
            PathAttribute{name:"iconScale";value: 0.8}
            PathPercent{value: 1.0}
        }
    }
    Image {
        id: list_cut_line0
        anchors { top: parent.top; topMargin: 287; left: parent.left; leftMargin: 64; }
        source: "./image/mainPage/list_cut_line.png"
    }
    Image {
        id: list_cut_line1
        anchors { top: parent.top; topMargin: 517; left: parent.left; leftMargin: 64; }
        source: "./image/mainPage/list_cut_line.png"
    }
    Connections{
        target: Thread
        onTime_start: {
            currentName = testname;
            timeOut.start();
        }
    }
    Connections{
        target: Thread
        onTime_stop: timeOut.stop();
    }
    Connections{
        target: Thread
        onNextOne: {
            testList.incrementCurrentIndex();
            //console.log("testList = %d", testList.currentIndex);
        }
    }

    Timer{
        id: timeOut
        interval: 10000
        repeat: false
        running: false
        onTriggered: {
            DataModel.setFileNamebyFilePath(currentName, "测试NG，错误代码0xFF");
            Thread.clear_socket();//套接字缓冲区进行清除
            //on_time_out();
        }
    }

    //此处不确定能成功
//    function on_time_out() {
//        var component = Qt.createComponent("tooltip.qml");
//        var bQml = component.createObject(test_list_section);
//        //bQml.time_out.connect(time_out);
//        bQml.errorName = currentName;
//        bQml.errorCode = 0xFF;//接收超时
//        tooltip.visible = true;//此处不确定能成功
//    }

    property int i: 0;
    property bool colorFlag: true;
    property string currentName:"";
}
