#include "loginnetworkmanager.h"
#include"mynetworker.h"
#include<QEventLoop>
LoginNetWorkManager::LoginNetWorkManager(QObject *parent) : QObject(parent)
{
    initCookie();
    connect(this,&LoginNetWorkManager::startNewChecker,this,&LoginNetWorkManager::initChecker);
    connect(this,&LoginNetWorkManager::startSecondSignal,this,&LoginNetWorkManager::startSecondRequest);
}

void LoginNetWorkManager::initCookie()
{
    QThread* localThread=new QThread(this);
    MyNetWorker *networker=new MyNetWorker(getCookieUrl,FUN::GET);
    networker->moveToThread(localThread);
    connect(localThread,&QThread::finished,networker,&QObject::deleteLater);
    connect(this,&LoginNetWorkManager::startCookie,networker,&MyNetWorker::start);
    connect(networker,&MyNetWorker::netConnectComplete,localThread,&QThread::quit);
    localThread->start();
    emit startCookie();
}

void LoginNetWorkManager::needNewQR()
{
    QThread* localThread=new QThread(this);
    MyNetWorker* networker=new MyNetWorker(QRcodeUrl,FUN::GET);
    networker->moveToThread(localThread);
    connect(localThread,&QThread::finished,networker,&QObject::deleteLater);
    connect(this,&LoginNetWorkManager::startQR,networker,&MyNetWorker::start);

    connect(networker,&MyNetWorker::netConnectComplete,[networker,this,localThread](){
        localThread->quit();
        QPixmap pixmap;
        pixmap.loadFromData(networker->readAll());
        emit getPix(pixmap);
        //刷新了二维码
        emit stopOldChecker();
        emit startNewChecker();
    });
    localThread->start();
    emit startQR();
}

void LoginNetWorkManager::initChecker()
{
    StatusChecker* checker=new StatusChecker();
    QThread* thread=new QThread(this);
    checker->moveToThread(thread);
    connect(thread,&QThread::destroyed,checker,&QObject::deleteLater);
    connect(this,&LoginNetWorkManager::stopOldChecker,thread,&QThread::quit);
    connect(this,&LoginNetWorkManager::startChecker,checker,&StatusChecker::run);
    connect(checker,&StatusChecker::QRisOK,[this,thread](QString name,QString url ){
        qDebug()<<"login success";
        //这里会有死锁,将sleep后置,可解决这个问题
        thread->quit();
        emit this->startSecondSignal(url);
        emit this->loginSuccess(name);
    });

    connect(checker,&StatusChecker::QRisOld,[](){

    });
    connect(checker,&StatusChecker::QRisWait,[](){

    });

    thread->start();
    emit startChecker();
}

void LoginNetWorkManager::startSecondRequest(QString url)
{

    //因为上轮询时,有两秒的sleep,然后线程对this上了锁,
    //所以这里会产生,死锁
    QThread* second=new QThread(this);
    MyNetWorker* worker=new MyNetWorker(url);
    worker->moveToThread(second);
    connect(second,&QThread::finished,worker,&MyNetWorker::deleteLater);
    connect(this,&LoginNetWorkManager::startSeconder,worker,&MyNetWorker::start);

    connect(worker,&MyNetWorker::netConnectComplete,[=](){
        qDebug()<<"success";

    });
    second->start();
    emit startSeconder();

}

StatusChecker::StatusChecker(QObject *parent):
    QObject(parent)
{
    getCheckStatusUrl();
}

void StatusChecker::getCheckStatusUrl()
{
    QString sig=MyNetWorker::cookieJar.getValueByName("qrsig");
    int e,i,n;
    for( e=0,i=0,n=sig.length();i<n;i++){
        e+=(e <<5)+sig[i].unicode();
    }

    QString qr_hash= QString::number(2147483647 & e);
    checkStatusUrl=QString("https://ssl.ptlogin2.qq.com/ptqrlogin?ptqrtoken=%1&webqq_type=10&remember_uin=1&login2qq=1&aid=501004106&u1=http%3A%2F%2Fw.qq.com%2Fproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=0-0-28321&mibao_css=m_webqq&t=undefined&g=1&js_type=0&js_ver=10226&login_sig=&pt_randsalt=0").arg(qr_hash);
}

void StatusChecker::run()
{
    //轮询
    while(true){
        QThread::sleep(2);
        MyNetWorker networker(checkStatusUrl,FUN::GET);
        networker.start();
        QEventLoop loop;
        connect(&networker,&MyNetWorker::netConnectComplete,&loop,&QEventLoop::quit);
        loop.exec();
        QByteArray array=networker.readAll();
        //开始进行切割字符串得到状态
        QString reString=array;
        QStringList slist=reString.split('\'');
        QString status=slist[1];
        /*
         * QString back=slist[5];  //返回的网址
         *QString message=slist[11]; //返回的个人昵称
        */
        if(status==QString("67")){
            //扫描但是没有确认
            emit QRisWait();

        }else if(status==QString("0")){
            //扫描并且确认
            emit QRisOK(slist[11],slist[5]);
            return;
        }else if(status==QString("65")){
            //二维码过期
            emit QRisOld();
        }
        qDebug()<<status;
    }
}
