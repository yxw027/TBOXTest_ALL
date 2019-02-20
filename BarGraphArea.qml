import QtQuick 2.0

Item {
    id:root
    width: 200
    height: 100
    //color: "white";
    property bool create_flag: true;
    property var barObject : [];
    property var component: Qt.createComponent("BarItem.qml");
    property real spacing: 5;
    property real barWidth: 15;
    property real barInteral: spacing+barWidth;
    property real barCount: 13
    function resetBarArea(){
        if(barObject.length <= 0)
            return;
        for(var i in barObject){
            barObject[i].destoryBarItem();
        }
        barObject.length = 0;
    }
    function createBarArea(){
        var object;
        for(var i = 0; i < barCount; i++){
            object = component.createObject(root,
                                            {
                                                "x":root.spacing + i*barInteral,
                                                "width":root.barWidth,
                                                "height":root.height,
                                                "anchors.bottom":root.bottom,
                                                "barHeight":0,
                                                "index": i.toString()
                                            });
            barObject.push(object);
        }
    }
    Image {
        id: gps_false_signal
        visible: true
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.leftMargin: 10
        source: "./image/gps_sig/gps_transparency.png"
    }

    Connections{//处理GPS信号柱状图
        target: Thread
        onGpsBarData: {
            gps_false_signal.visible = false;
            if(create_flag)
            {
                root.resetBarArea();
                root.createBarArea();
                create_flag = false;
            }
            for(var i=0; i<barCount; i++)
            {
                if(barObject[i].barHeight === 0)
                {
                    barObject[i].barHeight =  strengthNum*2;
                    if((0<strengthNum) && (strengthNum<=10))
                    {
                        barObject[i].barColor="red"
                    }
                    else if((10<strengthNum) && (strengthNum<=15))
                    {
                        barObject[i].barColor="coral"
                    }
                    else if((15<strengthNum) && (strengthNum<=20))
                    {
                        barObject[i].barColor="yellow"
                    }
                    else if(20<strengthNum)
                    {
                        barObject[i].barColor="green"
                    }
                    break;
                }
            }
        }
    }
    /*Timer{
        interval: 500;
        repeat: true;
        running: true;
        onTriggered: {
            if(barObject.length > 0){//生成随机数
                for(var i = 0; i < barCount; i++){
                    barObject[i].barHeight = Math.random()*root.height;
                    barObject[i].barHeight > 50 ? barObject[i].barColor="green" : barObject[i].barColor="yellow";
                }
            }
            else
            {
                root.resetBarArea();
                root.createBarArea();
            }
        }
    }*/
}
