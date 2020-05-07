import QtQuick 2.0

Item {
    id: mianpage
    width: parent.width;
    height: parent.height
    anchors.fill: parent
    
    Loader{
        id: bgSection
        anchors {
            top: parent.top;
            left: parent.left;
            fill: parent;
        }
        source: "./bgSection.qml"
    }

    Loader{
        id: carInfoSection
        anchors.top: parent.top;
        anchors.left: parent.left
        source: "./carInfoSection.qml"
    }

    Loader{
        id: testListSection
        anchors.top: parent.top;
        anchors.left: parent.left
        source: "./testListSection.qml"
    }

    Loader{
        id: gpsSection
        anchors.top: parent.top;
        anchors.left: parent.left
        source: "./gpsSection.qml"
    }
}
