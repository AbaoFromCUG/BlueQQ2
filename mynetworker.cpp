#include "mynetworker.h"
#include<QEventLoop>
MyNetworkCookieJar MyNetWorker::cookieJar;
MyNetWorker::MyNetWorker(QString Url,FUN fun,QObject *parent) : QObject(parent)
{
    function=fun;
    manager=new QNetworkAccessManager(this);
    request=new QNetworkRequest(Url);
    manager->setCookieJar(&cookieJar);
    cookieJar.setParent(0);
}

void MyNetWorker::setUrl(QString newUrl)
{
    this->request->setUrl(newUrl);
}

void MyNetWorker::setReferer(QString referer)
{
    //Referer
    QByteArray array=referer.toLocal8Bit();
    request->setRawHeader("Referer",array);
}

void MyNetWorker::setRawHeader(QString name, QString text)
{
    request->setRawHeader(name.toLocal8Bit(),text.toLocal8Bit());
}

void MyNetWorker::setAccept(QString accept)
{
    request->setRawHeader("Accept",accept.toLocal8Bit());
}

void MyNetWorker::setFun(FUN fun)
{
    this->function=fun;
}

void MyNetWorker::setPOSTData(QByteArray array)
{
    data=array;
}
//开始执行操作
void MyNetWorker::start()
{
    if(function==FUN::POST){
        reply=manager->post(*request,data);
    }else {
        reply=manager->get(*request);
    }

    connect(reply,&QNetworkReply::finished,[this](){
        emit this->netConnectComplete();
    });
}

QByteArray MyNetWorker::readAll()
{
    return reply->readAll();
}
