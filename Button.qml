import QtQuick 2.0


Item {
    id: button;
    anchors.fill: parent
    focus: false;

    property int ispressinputboxtext:0;
    property int textsize: 28
    property string centerText: ""
    property string normalSource;
    property string pressSource;
    property string btnText: "";
    property bool btnTextVisible: true;

    Image {
        id: normal;
        anchors.fill: parent;
        source: normalSource;
        visible: !button.focus;
    }

    Image {
        id: press;
        anchors.fill: parent;
        source: pressSource;
        visible: button.focus;
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 100
        text: btnText;
        font.pixelSize: textsize;
        color:ispressinputboxtext==0?"#ffffff":"#6252ff";
        //font.family: fontFamily;
        visible:btnTextVisible;
         font.family: fontFamily;
    }

    Text {
        anchors.centerIn: parent
        text: centerText;
        font.pixelSize: textsize;
        color:"#ffffff";
        //font.family: fontFamily;
         font.family: fontFamily;
    }

    MouseArea  {
        anchors.fill: parent;

        onCanceled: {
            button.focus = false;
        }

        onPressed: {
            button.focus = true;
            onButtonPressed(mouse.x, mouse.y);
        }

        onExited: {
            button.focus = false;
        }

        onReleased: {
            button.focus = false;
        }

        onClicked: {
            //console.log("cliked is be emit!!!");
            button.focus = false;
            onButtonClicked(mouse.x, mouse.y);
        }
    }

    signal pressed();
    signal pressedXY(int x, int y);
    signal clicked_m();
    signal clickedName(string appName);
    signal clickedXY(int x, int y);

    function onButtonPressed(x, y) {
        pressed();
        pressedXY(x, y);
    }
    function onButtonClicked(x, y) {
        var Msg = "onButtonClicked x:" + x + ",y:" + y;
        //globalObject.print(Msg);
        clicked_m();
        clickedName(btnText);
        clickedXY(x, y);
    }
}

