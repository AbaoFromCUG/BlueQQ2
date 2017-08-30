#ifndef MYDIALOGMANAGER_H
#define MYDIALOGMANAGER_H
#include"logindialog.h"
#include"welcomedialog.h"
#include <QObject>
#include<datamanager.h>
#include"aimdialog.h"
class MyDialogManager : public QObject
{
    Q_OBJECT
public:
    explicit MyDialogManager(QObject *parent = nullptr);
    void showLogin();

private:
    LoginDialog* login;
    WelcomeDialog* welcome;
    DataManager* dataManager;
    AimDialog* aimDialog;

signals:
    void workSig();

public slots:
    void showWlecome(QString);
    void mainWorker();

};

#endif // MYDIALOGMANAGER_H
