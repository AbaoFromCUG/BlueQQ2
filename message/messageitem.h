#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QObject>

class MessageItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imgSrc READ imgSrc WRITE setImgSrc NOTIFY imgSrcChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString uin READ uin WRITE setUin NOTIFY uinChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
public:
    explicit MessageItem(QObject *parent = nullptr);

    QString imgSrc() const;

    QString uin() const;

    int type() const;

    QString text() const;

    QString time() const;

    QString name() const;



public slots:
    void setImgSrc(const QString &imgSrc);
    void setName(const QString &name);
    void setUin(const QString &uin);
    void setType(int type);
    void setText(const QString &text);
    void setTime(const QString &time);
signals:
    void imgSrcChanged(QString arg);
    void nameChanged(QString arg);
    void uinChanged(QString arg);
    void typeChanged(int arg);
    void textChanged(QString arg);
    void timeChanged(QString arg);

protected:
    QString m_imgSrc ;
    QString m_name;
    QString m_uin;
    int m_type;
    QString m_text;
    QString m_time;

};



#endif // MESSAGEITEM_H
