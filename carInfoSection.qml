import QtQuick 2.0

Item {
    id: carInfo
    anchors.top: parent.top; anchors.left: parent.left
    
    Component{
        id: carInfoDelegate
        Item {
            id: wrapper;
            width: carIfo1.cellWidth;
            height: carIfo1.cellHeight;

            Text {
                id: tableName
                font.pixelSize: 22
                text: qsTr(FilePath+":")
                color: "white"
                font.family: fontFamily;
            }

            Text {
                id: tableInfo
                font.pixelSize: 22
                anchors.left: tableName.right
                text: qsTr(FileName)
                color: "white"
                font.family: fontFamily;
            }
        }
    }

    GridView{
        id: carIfo1
        anchors{
            top: parent.top;
            topMargin: 92;
            left: parent.left;
            leftMargin: 20;
        }
        width: 400;
        height: 100
        cellWidth: 400;
        cellHeight: 33
        model:TestNameModel
        delegate: carInfoDelegate
        interactive: false
    }
    
    Component{
        id: carInfoDelegate1
        Item {
            id: wrapper;
            width: carIfo2.cellWidth;
            height: carIfo2.cellHeight;

            Text {
                id: tableName
                font.pixelSize: 22
                text: qsTr(FilePath+":")
                color: "white"
                font.family: fontFamily;
            }

            Text {
                id: tableInfo
                font.pixelSize: 22
                anchors.left: tableName.right
                text: qsTr(FileName)
                color: "white"
                font.family: fontFamily;
            }
        }
    }

    GridView{
        id: carIfo2
        anchors {
            top: parent.top;
            topMargin: 92;
            left: carIfo1.right;
            leftMargin: 50;
        }
        width: 500;
        height: 100
        cellWidth: 500;
        cellHeight: 33
        model:TestNameMode2
        delegate: carInfoDelegate1
        interactive: false
    }
}


