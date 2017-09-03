    #include "mynetworkcookiejar.h"
    #include<QNetworkCookie>
    #include<QDebug>
    MyNetworkCookieJar::MyNetworkCookieJar()
    {
        /*pgv_info	"ssid=s1111547944"
         *pgv_pvid	"7719057724"
         * 因为在开发消息发送时,发生了我的小号可以发送消息,
         * 但是登录了其他号不可以发送消息,所以猜测是跟这两个数据有关
         * 猜测不能设置为不变
         */
        QNetworkCookie  pgvCookie("pgv_info","ssid=s2345559850");
        QNetworkCookie pvid_Cookie("pgv_pvid","7745622344");
        pgvCookie.setDomain(".qq.com");
        pvid_Cookie.setDomain(".qq.com");
        this->insertCookie(pgvCookie);
        this->insertCookie(pvid_Cookie);
    }

    QList<QNetworkCookie> MyNetworkCookieJar::getCookies()
    {
        return allCookies();

    }

    void MyNetworkCookieJar::setCookies(const QList<QNetworkCookie> &cookieList)
    {
        setAllCookies(cookieList);
    }

    QString MyNetworkCookieJar::getValueByName(QString _name)
    {
        QList<QNetworkCookie> list=this->getCookies();
        for(int i=0;i<list.length();i++){
            if(QString(list[i].name())==_name){
                return list[i].value();
            }
        }
        return "";
    }

