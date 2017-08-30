#ifndef DATABASEOPERATION_H
#define DATABASEOPERATION_H

#include <QObject>
#include<QSqlDatabase>
#include"message/chatmessageinfo.h"
/*
 * 设计的数据库
 * 用来存放所有接到的消息,发送的消息
 * 字段说明
 *  aimUin,senderUin, message mydate mytime
 * aimUin 来自哪个聊天人(群,讨论组)
 * senderUin 谁发送的,好友uin,群成员uin,讨论组成员id
 * type 类型
 *      * 1.群消息
 *      * 2.讨论组消息
 *      * 3. 好友消息
 */
class DatabaseOperation : public QObject
{
    Q_OBJECT
public:
    static QSqlDatabase sqlite_db;
    DatabaseOperation();
    ~DatabaseOperation();
    bool tableAvailable(const QString& tableName);//判断表名为tableName的表是可操作
private:
public slots:
    bool openSqlDatabase(const QString& userqq);//初始化数据库
    void closeSqlDatabase();
    void insertData(const QString& tableName, ChatMessageInfo *data);//向数据库中插入数据
    void insertDatas(const QString& tableName, ChatMessageInfoList *datas);//向数据库中插入多条数据
    //void getDatas(const QString& tableName, int count, ChatMessageInfo* currentData, ChatMessageInfoList *datas);
    //获取数据库中的count条数据，将获得的数据存入datas当中

};


#endif // DATABASEOPERATION_H
