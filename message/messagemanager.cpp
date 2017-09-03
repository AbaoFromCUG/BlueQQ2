#include "messagemanager.h"

QString MessageManager::sendFriendUrl="http://d1.web2.qq.com/channel/send_buddy_msg2";
QString MessageManager::sendGroupUrl="http://d1.web2.qq.com/channel/send_qun_msg2";
QString MessageManager::sendDiscuUrl="http://d1.web2.qq.com/channel/send_discu_msg2";
DataManager* MessageManager::data=NULL;
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

void MessageManager::poll2()
{
    PollNetworker* networker=new PollNetworker();
    QThread* thread=new QThread(this);
    networker->moveToThread(thread);
    connect(thread,&QThread::started,networker,&PollNetworker::startPoll);
    connect(networker,&PollNetworker::getMessage,[=](QString from_uin,ChatMessageInfo* message){
        this->addMessage(from_uin,message);
    });
    thread->start();

}

void MessageManager::addMessage(QString from_uin, ChatMessageInfo *message)
{
    if(!allMessage.contains(from_uin)){
        allMessage.insert(from_uin,new ChatMessageInfoList);

    }
    allMessage[from_uin]->append(message);
    emit messageChanged();
}





ChatMessageInfoList* MessageManager::getMessageListByUin(QString uin)
{
    return allMessage[uin];
}

QList<QObject*> MessageManager::getShowItem(QString from_uin)
{
    if(!allMessage.contains(from_uin)){
        return QList<QObject*>();
    }else {
        ChatMessageInfoList* list=allMessage[from_uin];
        QList<QObject*> mess;
        for(int i=0;i<list->length();i++){
            ChatMessageInfo* itemMessage=list->at(i);
            MessageItem *item=new MessageItem;
            item->setUin(itemMessage->senderUin());
            //
            item->setName(data->getFriendName(itemMessage->senderUin()));
            item->setTime(QDateTime(itemMessage->date(),itemMessage->time()).toString("yyyy-MM-dd hh:mm:ss"));
            item->setImgSrc(":/images/demon/3.jpeg");
            item->setText(itemMessage->contentData());
            int s=itemMessage->type()/10;
            if(s==0){
                item->setType(itemMessage->type());
            }else {
                item->setType(3+item->type()%10);
            }
            mess.append(item);
        }
        return mess;
    }
}

PollNetworker::PollNetworker() {

    poll2Url= "http://d1.web2.qq.com/channel/poll2";
}

PollNetworker::~PollNetworker() {}

void PollNetworker::startPoll()
{
    QThread::sleep(50);
    while (true) {
        doOncePoll();
    }

}

void PollNetworker::stopPoll()
{

}

void PollNetworker::doOncePoll()
{
    /*
     * 由于心跳包是串行的,且都是一直等待,直到超时(120s)
     */
    MyNetWorker request(poll2Url,FUN::POST);
    request.setRawHeader("Referer","http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2");
    request.setRawHeader("Accept","*/*");
    request.setRawHeader("Content-Type"," application/x-www-form-urlencoded");
    request.setRawHeader("DNT","1");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:55.0) Gecko/20100101 Firefox/55.0");

    QString str=QString("r={\"ptwebqq\":\"%1\",\"clientid\":53999199,\"psessionid\":\"%2\",\"key\":\"\"}").arg(MyNetWorker::cookieJar.getValueByName("ptwebqq")).arg(MessageManager::data->getPsessionid());
    //QString str=QString("r={\"ptwebqq\":\"\",\"clientid\":53999199,\"psessionid\":\"%1\",\"key\":\"\"}").arg(MessageManager::data->getPsessionid());
    QByteArray byte;
    byte.append(str);
    request.setPOSTData(byte);

    QEventLoop loop;
    connect(&request,&MyNetWorker::netConnectComplete,&loop,&QEventLoop::quit);
    request.start();
    loop.exec();
    QByteArray r=request.readAll();
    qDebug()<<r;
    QJsonObject resultObject=QJsonDocument::fromJson(r).object();
     int retcode=resultObject.value("retcode").toInt();
    if(retcode==100001){
        qDebug()<<resultObject.value("errmsg").toString();
    }else if(retcode==0){
        //正常返回
        QJsonArray messageArray=resultObject.value("result").toArray();
        if(messageArray.size()==0){
            //返回是空的,那么
            qDebug()<<resultObject.value("errmsg").toString();
        }else {
            //result不为空
            /*
             * "result": [{
                "poll_type": "discu_message",
                "value": {
                  "content": [
                    ["font", {
                      "color": "000000",
                      "name": "微软雅黑",
                      "size": 10,
                      "style": [0, 0, 0]
                    }], "测试啊不错的"
                  ],
                  "did": 4144638746,
                  "from_uin": 4144638746,
                  "msg_id": 2,
                  "msg_type": 5,
                  "send_uin": 3766685460,
                  "time": 1502972935,
                  "to_uin": 2121738163
                }
              }],
  */
            for(auto item:messageArray){
                int type;
                QJsonObject oneMessage=item.toObject();
                QString messageType=oneMessage.value("poll_type").toString();
                QJsonObject value=oneMessage.value("value").toObject();
                //解析value
                /*
                 * 一个消息内容
                 *
                 * 五个公共消息特征
                 */
                QString content=value.value("content").toArray()[1].toString();

                QString from_uin=QString::number((long long)value.value("from_uin").toDouble());
                int msg_id=value.value("msg_id").toInt();
                int msg_type=value.value("msg_type").toInt();
                long long time=(long long)value.value("time").toDouble();
                QDateTime msg_time=QDateTime::fromTime_t(time);
                QString to_uin=QString::number((long long)value.value("to_uin").toDouble());

                //组装成消息
                ChatMessageInfo *message=new ChatMessageInfo();
                message->setAimUin(from_uin);
                message->setContentData(content);
                message->setDate(msg_time.date());
                message->setTime(msg_time.time());
                message->setMessageId(msg_id);
                if(messageType=="message"){
                    //收到好友消息
                    /*
                     * 好友消息,就只需要以上几个公共特征
                     */
                    message->setType(MessageType::FriendMessage);
                }else if(messageType=="group_message"){
                    //收到群消息
                    QString send_uin=QString::number((long long)value.value("send_uin").toDouble());
                    message->setSenderUin(send_uin);
                    message->setType(MessageType::GroupMessage);
                }else if(messageType=="discu_message"){
                    //收到讨论组的消息
                    QString send_uin=QString::number((long long)value.value("send_uin").toDouble());
                    message->setSenderUin(send_uin);
                    message->setType(MessageType::Discu);
                }else {
                    //其他处理
                    qDebug()<<messageArray;
                }
                emit getMessage(from_uin,message);

            }
        }
    }

    if(retcode==103){
         qDebug()<<byte;
    }


}
