#include "datamanager.h"
#include<QThread>
#include<QJsonDocument>
#include"mynetworker.h"
#include<QTimer>
#include<QJsonObject>
#include<QEventLoop>
#include<QFile>
DataManager::DataManager(QObject *parent) : QObject(parent)
{
    loginReportUrl="http://d1.web2.qq.com/channel/login2";
    getFriendUrl="http://s.web2.qq.com/api/get_user_friends2";
    getGroupUrl="http://s.web2.qq.com/api/get_group_name_list_mask2";
}

DataManager::~DataManager(){
    killThread();
}

void DataManager::getVfwebqq()
{
    //先拼凑出URL,这个URL主要有两个关键数据,ptwebqq(Cookie)和时间戳组成
    QString webqq=MyNetWorker::cookieJar.getValueByName("ptwebqq");
    QString url=QString("http://s.web2.qq.com/api/getvfwebqq?ptwebqq=%1&clientid=53999199&psessionid=&t=%2").arg(webqq).arg(getT());
    //因为这个值是此后请求的关键值,所以不进行异步请求,就在主线程中进行
    //QThread* vfThread=new QThread();
    //list.append(vfThread);
    MyNetWorker networker(url);
    networker.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
    networker.setAccept("*/*");
    networker.start();
    QEventLoop loop;
    connect(&networker,&MyNetWorker::netConnectComplete,&loop,&QEventLoop::quit);
    loop.exec();
    QByteArray byte=networker.readAll();
    qDebug()<<"vfwebqq"<<byte;
    //开始解析
    QJsonObject object=QJsonDocument::fromJson(byte).object();
    int retcode=object.value("retcode").toInt();
    if(retcode!=0){
        qDebug()<<"getVfwebqq error";
        qDebug()<<url;
        getVfwebqq();
    }else {
        QJsonObject result=object.value("result").toObject();
        this->vfwebqq=result.value("vfwebqq").toString();
    }
}

void DataManager::loginReport()
{
    //数据准备
    QString ptwqq=MyNetWorker::cookieJar.getValueByName("ptwebqq");
    QByteArray data;        //post的数据
data.append(QString("r={\"ptwebqq\":\"%1\",\"clientid\":53999199,\"psessionid\":\"\",\"status\":\"online\"}").arg(ptwqq));
    QThread* thread=new QThread();
    list.append(thread);
    MyNetWorker* netWorker=new MyNetWorker(loginReportUrl,FUN::POST);
    netWorker->setPOSTData(data);
    netWorker->moveToThread(thread);
    connect(thread,&QThread::finished,netWorker,&MyNetWorker::deleteLater);
    connect(netWorker,&MyNetWorker::netConnectComplete,[=](){
       QByteArray array=netWorker->readAll();
       QJsonObject object=QJsonDocument::fromJson(array).object();
       if(object.value("retcode")!=0){
           qDebug()<<"loginReport"<<"fail, try again";
           loginReport();
       }else {
           loginMessage=object.value("result").toObject();

       }

    });
    thread->start();
    QTimer::singleShot(0,netWorker,&MyNetWorker::start);


}

void DataManager::getFriendList()
{
    QThread* gFThread=new QThread();
    list.append(gFThread);
    MyNetWorker* netWorker=new MyNetWorker(getFriendUrl,FUN::POST);
    netWorker->setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
    netWorker->setAccept("*/*");
    //{"vfwebqq":"2a75ae244061fb834d154555de406180a80da2e8aad97cb419d4c163f03fa71720e3e51da17feda8","hash":"07D654C309EE08ED"}
    QByteArray data;
    QString uin=MyNetWorker::cookieJar.getValueByName("uin");
    uin=uin.remove(0,1);
    QString ptwqq=MyNetWorker::cookieJar.getValueByName("ptwebqq");
    QString hashValue=badHash(uin,ptwqq);
    data.append(QString("r={\"vfwebqq\":\"%1\",\"hash\":\"%2\"}").arg(vfwebqq).arg(hashValue));
    //保存一下,下次得到群列表需要POST提交
    needMessag=data;
    netWorker->setPOSTData(data);
    netWorker->moveToThread(gFThread);
    connect(gFThread,&QThread::destroyed,netWorker,&MyNetWorker::deleteLater);
    connect(netWorker,&MyNetWorker::netConnectComplete,[=](){
        QByteArray array=netWorker->readAll();
        QJsonObject object=QJsonDocument::fromJson(array).object();
        int status=object.value("retcode").toInt();
        if(status!=0){
            qDebug()<<"getFriend  ERROR";
        }
        else {
            friendList=object.value("result").toObject();
            this->count++;
            if(count>=maxCount){
                emit getDataSuccess();
            }
        }
    });
    gFThread->start();
    QTimer::singleShot(0,netWorker,&MyNetWorker::start);
}

void DataManager::getGroupList()
{
    QThread* gGThread=new QThread();
    list.append(gGThread);
    MyNetWorker* netWorker=new MyNetWorker(getGroupUrl,FUN::POST);
    netWorker->setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
    netWorker->setAccept("*/*");
    netWorker->setPOSTData(needMessag);
    netWorker->moveToThread(gGThread);
    connect(gGThread,&QThread::destroyed,netWorker,&MyNetWorker::deleteLater);
    connect(netWorker,&MyNetWorker::netConnectComplete,[=](){
        QByteArray array=netWorker->readAll();
        QJsonObject object=QJsonDocument::fromJson(array).object();
        int status=object.value("retcode").toInt();
        if(status!=0){
            qDebug()<<"getGroup  ERROR";
        }
        else {
            groupList=object.value("result").toObject();
            this->count++;
            if(count>=maxCount){
                emit getDataSuccess();
            }
        }
    });
    gGThread->start();
    QTimer::singleShot(0,netWorker,&MyNetWorker::start);
}

void DataManager::getDiscusList()
{
    //先拼凑出URL,这个URL主要有两个关键数据,ptwebqq(Cookie)和时间戳组成
    QString pid=loginMessage.value("psessionid").toString();
    QString url=QString("http://s.web2.qq.com/api/get_discus_list?clientid=53999199&psessionid=%1&vfwebqq=%2&t=%3").arg(pid).arg(vfwebqq).arg(getT());

    QThread* gDThread=new QThread();
    list.append(gDThread);
    MyNetWorker* networker=new MyNetWorker(url);
    networker->setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
    networker->setAccept("*/*");
    networker->moveToThread(gDThread);
    connect(gDThread,&QThread::finished,networker,&MyNetWorker::deleteLater);
    connect(networker,&MyNetWorker::netConnectComplete,[=](){

        QJsonObject object=QJsonDocument::fromJson(networker->readAll()).object();
        int status=object.value("retcode").toInt();
        if(status!=0){
            qDebug()<<"get DiscusLIst error, let me try again";
            qDebug()<<url;
        }else {
            discusList=object.value("result").toObject();
            this->count++;
            if(count>=maxCount){
                emit getDataSuccess();
            }
        }
    });
    gDThread->start();
    QTimer::singleShot(0,networker,&MyNetWorker::start);
}

void DataManager::getSelfInfo()
{
    //http://s.web2.qq.com/api/get_self_info2?t=1502189237012
    QString url=QString("http://s.web2.qq.com/api/get_self_info2?t=%1").arg(getT());
    QThread* gSThread=new QThread();
    list.append(gSThread);
    MyNetWorker* networker=new MyNetWorker(url);
    networker->setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
    networker->setAccept("*/*");
    networker->moveToThread(gSThread);
    connect(gSThread,&QThread::finished,networker,&MyNetWorker::deleteLater);
    connect(networker,&MyNetWorker::netConnectComplete,[=](){
       QJsonObject object=QJsonDocument::fromJson(networker->readAll()).object();
       int status=object.value("return").toInt();
       if(status!=0){
           qDebug()<<"error  "<<url;
       }else {
           this->selfInfor=object.value("result").toObject();
           count++;
           if(count>=maxCount){
               emit getDataSuccess();
           }
       }
    });
    gSThread->start();
    QTimer::singleShot(0,networker,&MyNetWorker::start);
}

void DataManager::getRecentList()
{

}

//获得时间戳
QString DataManager::getT()
{
    QDateTime time=QDateTime::currentDateTime();   //获取当前时间
    long long cuo=time.toTime_t();
    long long c=1000*cuo+cuo/10000000;
    return QString("%1").arg(c);
}

int DataManager::getMessageId()
{
/*
 *   //用于生成msgid
        var sequence = 0;
        var t = (new Date()).getTime();
        t = (t - t % 1000) / 1000;
        t = t % 10000 * 10000;
        //获取msgId
        var getMsgId = function(){
            sequence++;
            return t + sequence;
        };
*/

    static int sequence = 0;
    QDateTime time=QDateTime::currentDateTime();   //获取当前时间
    long long t=time.toTime_t();
    t = t % 10000 * 10000;
    sequence++;
    return sequence+t;
}
//
//用来保存各种列表的
void DataManager::saveJSON()
{
    {
        QFile data("friend.json");
        QJsonDocument friendDoc(friendList);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QByteArray array=friendDoc.toJson();
            data.write(array);
            data.close();
        }
    }
    {
        QFile data("disscess.json");
        QJsonDocument friendDoc(discusList);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QByteArray array=friendDoc.toJson();
            data.write(array);
            data.close();
        }
    }
    {
        QFile data("group.json");
        QJsonDocument friendDoc(groupList);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QByteArray array=friendDoc.toJson();
            data.write(array);
            data.close();
        }
    }



}

QString DataManager::badHash(QString uin, QString ptwebqq)
{
    int ptb[4]={0,0,0,0};
    for (int i=0;i<ptwebqq.length();i++){
            int ptbIndex = i%4;
            ptb[ptbIndex] ^= ptwebqq[i].unicode();
    }
    QString salt[2]={"EC","OK"};
    int uinByte[4];
    uinByte[0] = (((uin.toLongLong() >> 24) & 0xFF) ^ salt[0][0].unicode());
    uinByte[1] = (((uin.toLongLong()  >> 16) & 0xFF) ^ salt[0][1].unicode());
    uinByte[2] = (((uin.toLongLong()  >> 8) & 0xFF) ^ salt[1][0].unicode());
    uinByte[3] = ((uin.toLongLong()  & 0xFF) ^ salt[1][1].unicode());
    int result1[8];
    for(int i=0;i<8;i++){
        if(i%2==0){
            result1[i]=ptb[i>>1];
        }else {
            result1[i] = uinByte[i>>1];
        }
    }
    QChar hex[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    QString buf;

      for (int i=0;i<8;i++){
          buf.append((hex[(result1[i]>>4) & 0xF]));
          buf.append((hex[result1[i] & 0xF]));
      }
      return buf;

}

QString DataManager::getFriendXByUin(QString X, QString uin)
{
    QString aim;
    if(X=="face"||X=="nick"){
        aim="info";
    }if(X=="markname"){
        aim="marknames";
    }
    QJsonArray Array=friendList.value(aim).toArray();
    for(auto index:Array){
        if(QString::number((long long)index.toObject().value("uin").toDouble())==uin){
            if(X=="face")
                return QString::number(index.toObject().value(X).toInt());
            return index.toObject().value(X).toString();
        }
    }
    //如果没有查询到,就返回空吧
    return "";
}

QString DataManager::getGroupXByUin(QString X, QString uin)
{
    QJsonArray array=groupList.value("gnamelist").toArray();
    for(auto item:array){
        if(QString::number((long long)item.toObject().value("gid").toDouble())==uin){
            return item.toObject().value(X).toString();
        }
    }
    return "";
}

QString DataManager::getDissXByUin(QString X, QString uin)
{
    QJsonArray array=discusList.value("dnamelist").toArray();
    for(auto item:array){
        if(QString::number((long long)item.toObject().value("did").toDouble())==uin){
            return item.toObject().value(X).toString();
        }
    }
    return "";
}

QString DataManager::getPsessionid()
{
    return loginMessage.value("psessionid").toString();
}


void DataManager::startInitData()
{
    getVfwebqq();
    loginReport();
    getFriendList();
    getGroupList();
    getDiscusList();
    getSelfInfo();


}

void DataManager::killThread()
{
    for(auto it:list){
        if(it->isRunning()){
            it->quit();
            it->wait();
        }
        if(it){
            delete it;
            it=NULL;
        }
    }

}
