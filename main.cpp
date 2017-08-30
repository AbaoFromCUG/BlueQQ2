#include "logindialog.h"
#include <QApplication>
#include<QCoreApplication>
#include<QQmlEngine>
#include"mydialogmanager.h"
#include"threadmanager.h"
#include"message/chatmessageinfo.h"
ThreadManager tmanager;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册模块
    //qmlRegisterType<ChatMessageInfo>("QQItemInfo", 1, 0, "ChatMessageInfo");
    qmlRegisterType<ChatMessageInfo>("ChatMessageInfo",1,0,"ChatMessageInfo");
    qmlRegisterType<ChatMessageInfoList>("ChatMessageInfo",1,0,"ChatMessageInfoList");
    MyDialogManager manager;
    manager.showLogin();
    return a.exec();
}
