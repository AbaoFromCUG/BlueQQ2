#include "downimg.h"
#include"mynetworker.h"
DownImg::DownImg(QString url,QObject *parent) : QObject(parent)
{
    this->Url=url;
}

void DownImg::start()
{
    MyNetWorker* networker=new MyNetWorker(Url);
    QThread *thread=new QThread(this);
    networker->moveToThread(thread);
    connect(thread,&QThread::finished,networker,&MyNetWorker::deleteLater);
    connect(this,&DownImg::startDown,networker,&MyNetWorker::start);
    connect(networker,&MyNetWorker::netConnectComplete,[=](){
        QPixmap pixmap;
        pixmap.loadFromData(networker->readAll());
        emit downSuccess(pixmap);
    });
    thread->start();
    emit startDown();

}
