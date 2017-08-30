#ifndef LOGINNETWORKMANAGER_H
#define LOGINNETWORKMANAGER_H

#include <QObject>
#include<QPixmap>
class LoginNetWorkManager : public QObject
{
    Q_OBJECT
public:
    explicit LoginNetWorkManager(QObject *parent = nullptr);
    void initCookie();
    void needNewQR();
    void initChecker();



signals:
    //向下的信号
    void startQR();
    void startCookie();
    void stopOldChecker();
    void startChecker();//向子线程通信开启run
    void startSeconder();
    //向自己的信号
    void startNewChecker();
    void startSecondSignal(QString);
    //向上的信号
    void getPix(QPixmap&);
    void loginSuccess(QString &name);
    void QRcodeWait();
    void QRcodeOld();



protected slots:
    void startSecondRequest(QString url);





protected:

    QString getCookieUrl="https://ui.ptlogin2.qq.com/cgi-bin/login?daid=164&target=self&style=16&mibao_css=m_webqq&appid=501004106&enable_qlogin=0&no_verifyimg=1&s_url=http%3A%2F%2Fw.qq.com%2Fproxy.html&f_url=loginerroralert&strong_login=1&login_state=10&t=20131024001";
    QString  QRcodeUrl="https://ssl.ptlogin2.qq.com/ptqrshow?appid=501004106&amp;e=0&amp;l=M&amp;s=5&amp;d=72&amp;v=4&amp;t=0.37886058497749353";
};


class StatusChecker:public QObject{
    Q_OBJECT
public:
    StatusChecker(QObject * parent=0);
    void getCheckStatusUrl();


public slots:
    void run();
protected:
    QString checkStatusUrl="";

protected:


signals:
    void QRisOld();
    void QRisWait();
    void QRisOK(QString& name,QString& url);



};

#endif // LOGINNETWORKMANAGER_H
