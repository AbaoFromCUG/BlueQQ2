import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import ChatMessageInfo 1.0


Item {
    id: root
    ListView{
       id: listView
       anchors.fill: parent
        model:myModel
        delegate:MessageItem{
            /*
            m_img: "./images/demon/friend.jpg"
            m_name: "Abao"
            m_text: "蒋劲是个大傻逼,大啊大傻逼,大大傻逼,大啊大傻逼"
            m_time: "12/13/21:12"
            state: "group"
            */

            m_name: name
            m_img: imgSrc
            m_text: text
            m_time:time
            state: {
                switch(type){
                case 1:
                case 2:
                    return "group"
                    break;
                case 3:
                    return "friend"
                    break;
                default:
                    return "self";
                    break;

                }
            }

        }




    }


}

