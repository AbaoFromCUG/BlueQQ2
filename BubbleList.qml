import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import ChatMessageInfo 1.0


Item {
    id: root
    ListView{
       id: listView
       anchors.fill: parent
        model:5  //myModel
        delegate:myItem

        Component {
            id:myItem
            MessageItem{
                /*
                m_img: "./images/demon/friend.jpg"
                m_name: "Abao"
                m_text: "蒋劲是个大傻逼,大啊大傻逼,大大傻逼,大啊大傻逼"
                m_time: "12/13/21:12"
                state: "group"
                */

                m_name: name
                m_img: imgSrc
                m_text: model.modelData.text
                m_time: model.modelData.time
                state: "group"



            }

        }

    }
    MouseArea{
        width: 100
        height: 100

        onClicked: {
            console.log(listView.model)
        }
    }

}

