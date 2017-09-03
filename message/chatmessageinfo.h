#ifndef CHATMESSAGEINFO_H
#define CHATMESSAGEINFO_H

#include <QObject>
#include <QtSql>
#include <QSettings>
#include <QObject>
#include <QDate>
#include <QTime>
#include <QQueue>
#include <QThread>
#include <QPointer>
#include <QTimer>
#include <QString>
#include <QDir>

/*
 * 提供消息相关的处理
 */
enum MessageType{
    //设置为123,而不是默认的0,1,2
    GroupMessage=1,   //收到的群消息
    Discu=2,           //收到的讨论组消息
    FriendMessage=3,   //收到的好友消息
    SelfGroup=11,       //发送的的群消息
    SelfDiscu=12,       //发送的讨论组消息
    SelfFriend=13       //发送给好友的消息
};
class ChatMessageInfo : public QObject
{
    Q_OBJECT
public:
    explicit ChatMessageInfo(QObject *parent = nullptr);
    virtual ~ChatMessageInfo();
    /*
     * 因为一开始架构有问题,在后续的代码编写中,
     * 发现ChatMessageInfo并不适合用来传递数据,
     * 所以就不需要一下代码来方便注册这些东西了
     * 而是采用MessageItem来单纯保存每个item需要的数据
     * 在传递的时候,先通过消息管理器来获取ChatMessageInfo的队列,
     * 然后转换为MessageItem来简化传值过程,
     * 繁琐,在下次迭代需要优化
     */
/*
    Q_PROPERTY(QString aimUin READ aimUin WRITE setAimUin NOTIFY aimUinChanged)  //从哪个uin收到的,如gruoupId friendId
    Q_PROPERTY(QString senderUin READ senderUin WRITE setSenderUin NOTIFY senderUinChanged)
    Q_PROPERTY(QString contentData READ contentData WRITE setContentData NOTIFY contentDataChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)//储存收到此条信息的日期
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)//储存收到此条信息的时间
    Q_PROPERTY(int messageId READ messageId)
    Q_PROPERTY(int messageId2 READ messageId2 WRITE setMessageId2 NOTIFY messageId2Changed)
    Q_PROPERTY(MessageType type READ type WRITE setType)

*/

    QString aimUin();

    QString senderUin();

    QString contentData();

    QDate date();

    QTime time();

    int messageId();

    //int messageId2();

    MessageType type();


signals:
    void aimUinChanged(QString arg);
    void senderUinChanged(QString arg);
    void contentDataChanged(QString arg);
    void dateChanged(QDate argDate);
    void timeChanged(QTime argTime);
    //void messageId2Changed(int argId);
public slots:
    void setAimUin(const QString &aimUin);
    void setSenderUin(const QString &senderUin);
    void setContentData(const QString &contentData);
    void setDate(const QDate &date);
    void setTime(const QTime &time);
    void setMessageId(int messageId);
    //void setMessageId2(int messageId2);
    void setType(const MessageType &value);
private:
    QString m_aimUin;
    QString m_senderUin;
    QString m_contentData;
    QDate m_date;
    QTime m_time;
    int m_messageId;
    //int m_messageId2;
    MessageType m_type;

};
/*
 * 这个类主要作为ChatMessageInfoList的一个容器
 * 性质是队列
 * 先进先出,
 * 后进后出
 */
class ChatMessageInfoList : public QObject
{
    Q_OBJECT
public:
    ChatMessageInfoList();
    virtual ~ChatMessageInfoList();
private:
    //以队列形式存储消息
    //关于队列http://doc.qt.io/qt-5/qqueue.html#dequeue

    QQueue<ChatMessageInfo*> list;
public slots:
    ChatMessageInfo* at(int index);
    //实现队列的基本功能
    int length();
    int size();
    void append(ChatMessageInfo* info);
    void insert(int pos,ChatMessageInfo* info);
    //销毁自己
    void destroy();
    void clear();
    /*
     * 数据结构QAQ
     * 出队,把头上的一个拿出
     * Removes the head item in the queue and returns it.
     * This function assumes that the queue isn't empty.
     */
    ChatMessageInfo* dequeue();
    ChatMessageInfo* find(int messageId);
};

class GroupInfo : public QObject
{
    Q_OBJECT
public:
    GroupInfo() {}
    virtual ~GroupInfo() {}
};




#endif // CHATMESSAGEINFO_H
