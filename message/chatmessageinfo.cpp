#include "chatmessageinfo.h"

ChatMessageInfo::ChatMessageInfo(QObject *parent) : QObject(parent)
{

}

ChatMessageInfo::~ChatMessageInfo()
{

}

void ChatMessageInfo::setAimUin(const QString &aimUin)
{
    m_aimUin = aimUin;
}

QString ChatMessageInfo::aimUin()
{
    return this->m_aimUin;
}

void ChatMessageInfo::setSenderUin(const QString &senderUin)
{
    m_senderUin = senderUin;
}

QString ChatMessageInfo::senderUin()
{
    return this->m_senderUin;
}

void ChatMessageInfo::setContentData(const QString &contentData)
{
    if(m_contentData!=contentData){
        m_contentData = contentData;
        emit contentDataChanged(contentData);
    }
}

QString ChatMessageInfo::contentData()
{
    return this->m_contentData;
}

void ChatMessageInfo::setDate(const QDate &date)
{
    if(m_date!= date){
        m_date = date;
        emit dateChanged(date);
    }
}

QDate ChatMessageInfo::date()
{
     return this->m_date;
}


void ChatMessageInfo::setTime(const QTime &time)
{
    if(m_time != time){
        m_time = time;
        emit timeChanged(time);
    }
}

QTime ChatMessageInfo::time()
{
    return this->m_time;
}

void ChatMessageInfo::setMessageId(int messageId)
{
    m_messageId = messageId;
}

int ChatMessageInfo::messageId()
{
    return this->m_messageId;
}
/*
void ChatMessageInfo::setMessageId2(int messageId2)
{
    if(m_messageId2 != messageId2){
        m_messageId2 = messageId2;
        emit messageId2Changed(messageId2);
    }
}
*/
void ChatMessageInfo::setType(const MessageType &value)
{
    m_type = value;
}
/*
int ChatMessageInfo::messageId2()
{
    return this->m_messageId2;
}
*/

MessageType ChatMessageInfo::ChatMessageInfo::type()
{
    return this->m_type;
}

