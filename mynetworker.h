#ifndef MYNETWORKER_H
#define MYNETWORKER_H

#include <QObject>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QThread>
#include<QByteArray>
#include"mynetworkcookiejar.h"

/*
 * 这封装了我的所有http请求
 * 所有请求共用一个CookieJar来管理Cookie
 * 提供一些方法
 * 但是需要注意的是,我这并不支持异步,也没有开线程,所以如果直接使用会造成线程阻塞
 */
enum FUN{
    POST,GET
};
class MyNetWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyNetWorker(QString Url,FUN fun=FUN::GET,QObject *parent = nullptr);
    void setUrl(QString newUrl);
    void setReferer(QString referer);
    void setRawHeader(QString name,QString text);
    void setAccept(QString accept);
    void setFun(FUN fun);
    void setPOSTData(QByteArray array);

    QByteArray readAll();


signals:
    void netConnectComplete();

public slots:
    void start();

protected:
    QNetworkAccessManager* manager;
    QNetworkRequest* request;
    QNetworkReply* reply;

    FUN function;
    QByteArray data;



public:
    static MyNetworkCookieJar cookieJar;

};


#endif // MYNETWORKER_H
