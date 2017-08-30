#include "databaseoperation.h"



QSqlDatabase DatabaseOperation::sqlite_db;
DatabaseOperation::DatabaseOperation()
{
    if (!sqlite_db.isValid()){
        //如果数据库无效，则进行初始化
        sqlite_db = QSqlDatabase::addDatabase ("QSQLITE");
    }
}

bool DatabaseOperation::tableAvailable(const QString &tableName)
{
    if(tableName!=""&&sqlite_db.isOpen ()){//如果数据库已经打开
        QString temp = "create table if not exists "+tableName+
                "(myindex INTEGER,aimUin VARCHAR[12],senderUin VARCHAR[12],message TEXT,mydate DATE,mytime TIME,type INT)";
        //创建一个表，如果这表不存在，表的列为aimUin,senderUin, message mydate mytime type
        QSqlQuery query = sqlite_db.exec (temp);
        if(query.lastError ().type ()==QSqlError::NoError){//如果上面的语句执行没有出错
            return true;
        }else{
            qDebug()<<"执行"<<temp<<"出错："<<query.lastError ().text ();
        }
    }else{
        qDebug()<<"数据库未打开";
    }
    return false;
}

bool DatabaseOperation::openSqlDatabase(const QString &userqq)
{
    if(!sqlite_db.isOpen ()){//如果数据库未打开
            sqlite_db = QSqlDatabase::addDatabase("QSQLITE");


            return sqlite_db.open ();
        }
        return true;}

void DatabaseOperation::closeSqlDatabase()
{
    sqlite_db.close ();
}

void DatabaseOperation::insertData(const QString &tableName, ChatMessageInfo *data)
{
    if(tableAvailable (tableName)){//判断表是否可以操作
        QString temp = "insert into "+tableName+
                " values(:myindex,:aimUin,:senderUin,:message,:mydate,:mytime,:type)";
        QSqlQuery insert_query;
        insert_query.prepare (temp);
        int index = sqlite_db.exec ("select count(*) from "+tableName).size ()+1;//设置此条数据的索引值
        insert_query.bindValue (":myindex", index);//设置数据的索引值（为此条数据的唯一标识）
        insert_query.bindValue(":aimUin",data->aimUin());
        insert_query.bindValue (":senderUin", data->senderUin());
        insert_query.bindValue (":message", data->contentData()); //要不要加密消息呢?,暂时不加密

        insert_query.bindValue (":mydate", data->date());
        insert_query.bindValue (":mytime", data->time());
        insert_query.bindValue(":type",data->type());
        if(insert_query.exec ()){//如果上面的语句执行没有出错
            //qDebug()<<"插入数据成功";
        }else{
            qDebug()<<"执行"<<temp<<"出错："<<insert_query.lastError ().text ();
        }
    }
}

void DatabaseOperation::insertDatas(const QString &tableName, ChatMessageInfoList *datas)
{
    //插入多条数据,开启事务
    if(tableAvailable(tableName)){ //如果表可以操作
        sqlite_db.transaction ();//开启事务操作
        for (int i=0;i<datas->size ();++i) {
            ChatMessageInfo* data = datas->at (i);
            if(data!=NULL){
                insertData (tableName, data);
            }
        }
        if(sqlite_db.commit ()){//提交事务操作,如果上面的语句执行没有出错
            qDebug()<<"插入"+QString::number (datas->size ())+"条数据成功";
        }else{
            qDebug()<<"执行多条插入出错："<<sqlite_db.lastError ().text ();
        }
    }

}

DatabaseOperation::~DatabaseOperation()
{
    closeSqlDatabase();
}



ChatMessageInfoList::ChatMessageInfoList() {}

ChatMessageInfoList::~ChatMessageInfoList() {}

ChatMessageInfo *ChatMessageInfoList::at(int index)
{
    return list.at(index);
}

int ChatMessageInfoList::length()
{
    return list.length();
}

int ChatMessageInfoList::size()
{
    return length();
}

void ChatMessageInfoList::append(ChatMessageInfo *info)
{
    list.append(info);
}

void ChatMessageInfoList::insert(int pos, ChatMessageInfo *info)
{
    list.insert(pos,info);
}

void ChatMessageInfoList::destroy()
{
    clear();
    this->deleteLater();
}

void ChatMessageInfoList::clear()
{
    //由于我们实例化ChatMessageInfo是没有指定parent,
    //直接向堆中申请,如果不回收,就会内存泄漏,所以我们需要手动回收每个消息的内存
    //额,下面是Java方式的遍历,Qt也支持,呃呃
    //也可以用古老的for(;;;)
    //或者C++11中的for(:)
    foreach (ChatMessageInfo* item, list) {
        //防止重复回收,直接崩溃
        if(item!=NULL){
            item->deleteLater();
        }
    }
    list.clear();
}

ChatMessageInfo *ChatMessageInfoList::dequeue()
{
    return list.dequeue();
}

ChatMessageInfo *ChatMessageInfoList::find(int messageId)
{
    foreach (ChatMessageInfo* item, list) {
        if(item!=NULL&&item->messageId()==messageId){
            return item;
        }
    }
    return NULL;
}
