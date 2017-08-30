#ifndef DOWNIMG_H
#define DOWNIMG_H

#include <QObject>
#include<QPixmap>
#include<QString>

class DownImg : public QObject
{
    Q_OBJECT
public:
    explicit DownImg(QString url,QObject *parent = nullptr);

protected:
    QString Url;
signals:
    void startDown();
    void downSuccess(QPixmap&);

public slots:
    void start();
};

#endif // DOWNIMG_H
