#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>
#include"mynetworker.h"
#include"chatmessageinfo.h"
#include"datamanager.h"
class MessageManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageManager(QObject *parent = nullptr);
    int     getMessageId();

signals:
    void sendSuccess();

public slots:
    void sendMessageToX(int X,QString uin, QString text);
    void setDataManager(DataManager *m);
    void sendMeeageToFriend(QString uin,QString text);
    void sendMessageToGroup(QString uin,QString text);
    void sendMessageToDiscu(QString uin, QString text);

    void sendSuccessSLOT();
private:
    QHash<QString,ChatMessageInfoList*> allMessage;
    DataManager* data;
    ChatMessageInfoList* getMessageListByUin(QString uin);
    static QString sendFriendUrl;
    static QString sendGroupUrl;
    static QString sendDiscuUrl;
    void dealMessage(QJsonObject message);
    void dealMessage(QString uin,QString text);
};

#endif // MESSAGEMANAGER_H
