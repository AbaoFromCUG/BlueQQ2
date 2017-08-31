#include "messageitem.h"

MessageItem::MessageItem(QObject *parent) : QObject(parent)
{
    m_imgSrc="../images/demon/3.jpeg";
    m_name="demon";
    m_text="texfdsfjasdfkjdjfafjkldjlk这是样例文字t";
    m_time="13/34/23:23";
    m_uin="uin";
}

QString MessageItem::imgSrc() const
{
    return m_imgSrc;
}

QString MessageItem::uin() const
{
    return m_uin;
}


int MessageItem::type() const
{
    return m_type;
}

QString MessageItem::text() const
{
    return m_text;
}

QString MessageItem::time() const
{
    return m_time;
}

void MessageItem::setImgSrc(const QString &imgSrc)
{

        m_imgSrc = imgSrc;
}

void MessageItem::setUin(const QString &uin)
{
    if(m_uin!=uin)
    m_uin = uin;

}



void MessageItem::setTime(const QString &time)
{
    m_time = time;
}

void MessageItem::setName(const QString &name)
{
    m_name = name;
}

QString MessageItem::name() const
{
    return m_name;
}

void MessageItem::setText(const QString &text)
{
    m_text = text;
}

void MessageItem::setType(int type)
{
    m_type = type;
}


