#include "messagemanager.h"

QString MessageManager::sendFriendUrl="http://d1.web2.qq.com/channel/send_buddy_msg2";
QString MessageManager::sendGroupUrl="http://d1.web2.qq.com/channel/send_qun_msg2";
QString MessageManager::sendDiscuUrl="http://d1.web2.qq.com/channel/send_discu_msg2";
MessageManager::MessageManager(QObject *parent) : QObject(parent)
{
    //connect(this,SIGNAL(sendSuccess(QString)),this,SLOT(sendSuccessSLOT(QString));
}

void MessageManager::sendMessageToX(int X, QString uin, QString text)
{
    MyNetWorker* netWorker;
    QString aimStr;
    switch (X) {
    case 0:
        aimStr="group_uin";
        netWorker=new  MyNetWorker(sendGroupUrl,FUN::POST,this);
        break;
    case 1:
        aimStr="did";
        netWorker=new MyNetWorker(sendDiscuUrl,FUN::POST,this);
        break;
    case 2:
        aimStr="to";
        netWorker=new  MyNetWorker(sendFriendUrl,FUN::POST,this);
        break;
    default:
        break;
    }

    QString str;
    QByteArray byte;
    QString face=data->getFriendXByUin("face",uin);
    str=QString::fromLocal8Bit("r={\"%0\":%1,\"content\":\"[\\\"%2\\\",[\\\"font\\\",{\\\"name\\\":\\\"宋体\\\",\\\"size\\\":10,\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"face\":%3,\"clientid\":53999199,\"msg_id\":%4,\"psessionid\":\"%5\"}").arg(aimStr).arg(uin).arg(text).arg(face).arg(data->getMessageId()).arg(data->loginMessage.value("psessionid").toString());
    byte.append(str);
    netWorker->setPOSTData(byte);
    netWorker->setReferer("http://d1.web2.qq.com/cfproxy.html?v=20151105001&callback=1");
    netWorker->setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:55.0) Gecko/20100101 Firefox/55.0");
    netWorker->setAccept("*/*");
    QThread *thread=new  QThread(this);
    netWorker->moveToThread(thread);
    connect(thread,&QThread::started,netWorker,&MyNetWorker::start);
    connect(thread,&QThread::finished,netWorker,&MyNetWorker::deleteLater);
    connect(netWorker,&MyNetWorker::netConnectComplete,[=]{
        QByteArray byte=netWorker->readAll();
        QJsonObject object=QJsonDocument::fromJson(byte).object();
        int status=object.value("errCode").toInt();
        if(status==0){
            qDebug()<<"sendSuccess";
            emit sendSuccess();
        }else {
            qDebug()<<str;
            qDebug()<<"send fail";
        }

    });
    thread->start();


}

void MessageManager::setDataManager(DataManager *m)
{
    this->data=m;
}

void MessageManager::sendMeeageToFriend(QString uin, QString text)
{

    sendMessageToX(2,uin,text);
    ChatMessageInfo* chat=new ChatMessageInfo();
    chat->setAimUin(uin);
    chat->setContentData(text);
    allMessage[uin]->append(chat);
}

void MessageManager::sendMessageToGroup(QString uin, QString text)
{
    sendMessageToX(0,uin,text);
}

void MessageManager::sendMessageToDiscu(QString uin, QString text)
{
    sendMessageToX(1,uin,text);

}

void MessageManager::sendSuccessSLOT()
{

}

ChatMessageInfoList* MessageManager::getMessageListByUin(QString uin)
{
    return allMessage[uin];
}
