import QtQuick 2.0

Rectangle {
    id: root;
    height: 290;
    width: 217;
    color: "#66ccff"
    function screenShot(){
        root.grabToImage(function(result){result.saveToFile("bbb.jpg");})
    }
}
