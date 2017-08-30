#ifndef MYNETWORKCOOKIEJAR_H
#define MYNETWORKCOOKIEJAR_H
#include<QNetworkCookieJar>
#include<QList>


class MyNetworkCookieJar : public QNetworkCookieJar
{
public:
    MyNetworkCookieJar();
    QList<QNetworkCookie> getCookies();
    void setCookies(const QList<QNetworkCookie>& cookieList);
    QString getValueByName(QString _name);


};

#endif // MYNETWORKCOOKIEJAR_H
