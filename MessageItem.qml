import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id:root
    width: parent.width
    height: time.y+time.height
    property string m_name;
    property string m_img;
    property string m_text;
    property string m_time;
    Text {
        id: name
        width: 150
        height: 15
        text: m_name
        font.pixelSize: 12
    }

    Image {
        id: avatar
        width: 40
        height: 40
        source: m_img
    }

    BorderImage {
        id: borderImage
        width: mainText.width+30
        height: mainText.height+30
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch

        source: "images/widgets/budder.png"

        Text {
            id: mainText
            width: root.width/2-30
            text: m_text
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 12
        }
    }

    Text {
        id: time
        color: "#323232"
        text: m_time
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideLeft
        wrapMode: Text.WordWrap
        font.pixelSize: 12
    }
    states: [
        State {
            name: "group"

            PropertyChanges {
                target: avatar
                x: 10
                y: 5
            }

            PropertyChanges {
                target: name
                x: 60
                y: 5
            }

            PropertyChanges {
                target: borderImage
                x: 55
                y: 25
                border.bottom: 30
                border.top: 15
                border.right: 30
                border.left: 15
            }

            PropertyChanges {
                target: mainText
                x: 13
                y: 13
            }

            PropertyChanges {
                target: time
                anchors.right: borderImage.right
                anchors.rightMargin: 0
                anchors.top: borderImage.bottom
                anchors.bottomMargin: 0
            }
        },
        State {
            name: "self"

            PropertyChanges {
                target: avatar
                anchors.right:root.right
                anchors.rightMargin: 10
                anchors.top: root.top
                anchors.topMargin: 5
            }
            PropertyChanges {
                target: name
                visible: false
                horizontalAlignment: Text.AlignRight
                anchors.right:avatar.left
                anchors.rightMargin: 10
                anchors.top: root.top
                anchors.topMargin: 5
            }
            PropertyChanges {
                target: borderImage
                border.bottom: 30
                border.top: 15
                border.right: 15
                border.left: 30
                source: "images/widgets/budder2.png"
                anchors.right:root.right
                anchors.rightMargin: 55
                anchors.top: root.top
                anchors.topMargin: 10
            }

            PropertyChanges {
                target: mainText
                anchors.right: borderImage.right
                anchors.rightMargin: 13
                anchors.top:borderImage.top
                anchors.topMargin: 13
            }

            PropertyChanges {
                target: time
                anchors.left: borderImage.left
                anchors.leftMargin: 0
                anchors.top:borderImage.bottom
            }
        },
        State {
            name: "friend"
            PropertyChanges {
                target: avatar
                x: 10
                y: 5
            }

            PropertyChanges {
                target: name
                x: 60
                y: 5
                visible: false
            }

            PropertyChanges {
                target: borderImage
                x: 55
                y: 10
                border.left: 15
                border.top: 15
                border.bottom: 30
                border.right: 30
            }

            PropertyChanges {
                target: mainText
                x: 13
                y: 13
            }

            PropertyChanges {
                target: time
                anchors.bottomMargin: 0
                anchors.right: borderImage.right
                anchors.top: borderImage.bottom
                anchors.rightMargin: 0
            }
        }
    ]

}
