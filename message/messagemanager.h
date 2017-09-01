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

    void poll2();


    void addMessage(QString from_uin,ChatMessageInfo* message);
public:

    QHash<QString,ChatMessageInfoList*> allMessage;
    static DataManager* data;
    ChatMessageInfoList* getMessageListByUin(QString uin);
    static QString sendFriendUrl;
    static QString sendGroupUrl;
    static QString sendDiscuUrl;
};

class PollNetworker : public QObject
{
    Q_OBJECT
public:
    PollNetworker();
    virtual ~PollNetworker();
public slots:
    void startPoll();
    void stopPoll();
    void doOncePoll();




signals:
    void getGroupMessage(ChatMessageInfo* message);
    void getDiscusMessage(ChatMessageInfo* message);
    void getFriendMessage(ChatMessageInfo* message);

protected:
    QString poll2Url ;
};
#endif // MESSAGEMANAGER_H
