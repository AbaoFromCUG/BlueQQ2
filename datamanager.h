#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include<QThread>
#include <QObject>
#include<QJsonObject>
#include<QJsonArray>
#include<QList>
/*
 * 这个类,既是数据的管理者(下载更新),也是数据的持有者(容器)
 * 为了简便,都用JSON来存
 * 但是架构不太好,在迭代中需要优化线程管理
 */
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();
    void saveJSON();
    int getMessageId();

private:
    //准备区
    void getVfwebqq();          //获取关键鉴权信息
    void loginReport();         //发送请求说明自己登录成功
    //功能区
    void getFriendList();       //获取好友列表
    void getGroupList();        //获取群列表
    void getDiscusList();       //获取讨论组列表
    void getSelfInfo();         //获取自己的信息
    void getRecentList();           //获取最近聊天列表

    QString getT();



    QString badHash(QString uin,QString ptwebqq);

public:
    //决定自己管理这些并行的线程,防止死锁,特别是当设置parent时
    QList<QThread*> list;
    QJsonObject loginMessage;
    QJsonObject friendList;
    QJsonObject groupList;
    QJsonObject discusList;
    QJsonObject selfInfor;


    QString getFriendXByUin(QString X, QString uin);
    QString getGroupXByUin(QString X,QString uin);
    QString getDissXByUin(QString X,QString uin);


    QString getFriendName(QString uin);
    QString getPsessionid();
    //其他关键数据
    QString vfwebqq;
    QString loginReportUrl;
    QString getFriendUrl;
    QString getGroupUrl;
    QString psessionid;
    QByteArray needMessag;

    //完成度
    int count=0;
    const int maxCount=6;


signals:
    void getDataSuccess();
    void doOneStep();

public slots:
    void startInitData();
    void killThread();

};

#endif // DATAMANAGER_H
