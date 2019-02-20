import QtQuick 2.0

Item {
    id: mianpage
    width: parent.width; height: parent.height
    anchors.fill: parent
    
    Loader{
        id: bgSection
        anchors { top: parent.top; left: parent.left; fill: parent; }
        source: "./bgSection.qml"
    }
    Loader{
        id: carInfoSection
        anchors.top: parent.top; anchors.left: parent.left
        source: "./carInfoSection.qml"
    }
    Loader{
        id: testListSection
        anchors.top: parent.top; anchors.left: parent.left
        source: "./testListSection.qml"
//        onLoaded: {//item.normalSource = "./image/tooltip/option_n.png";
//            item.time_out.connect(on_time_out);
//        }
    }
    Loader{
        id: gpsSection
        anchors.top: parent.top; anchors.left: parent.left
        source: "./gpsSection.qml"
    }

//    function on_time_out(errorName, errorCode) {
//        time_out(errorName, errorCode);
//    }
//    signal time_out( string errorName, int errorCode);
}
