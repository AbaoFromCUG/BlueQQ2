import QtQuick 2.0
import QtQuick.Controls 2.0
//import ChatMessageInfo 1.0
import QtQuick.Window 2.2

Item {
    id: root;
    function addItem(){
        listM.append()
    }

    ListView{
       id: listView
        anchors.fill: parent
        delegate: del
        model: listM;
        Component{
            id:del;
            MessageItem{
                /*
                m_img: "./images/demon/friend.jpg"
                m_name: "Abao"
                m_text: "蒋劲是个大傻逼,大啊大傻逼,大大傻逼,大啊大傻逼"
                m_time: "12/13/21:12"
                state: "self"
                */
                m_img: _img
                m_name:_name
                m_text: _text
                m_time:_time
                state:_state
            }
        }
        ListModel{
            id:listM
            ListElement{
                _img: "./images/demon/friend.jpg"
                _name: "Abao"
                _text: "蒋劲是个大傻逼,大啊大傻逼,大大傻逼,大啊大傻逼"
                _time: "12/13/21:12"
                _state: "self"
            }
        }
   }



}
