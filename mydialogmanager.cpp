#include "mydialogmanager.h"
#include<QTimer>
#include<QDebug>

MyDialogManager::MyDialogManager(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(workSig()),this,SLOT(mainWorker()));
}

void MyDialogManager::showLogin()
{
    login=new LoginDialog();
    login->show();
    connect(login,&LoginDialog::loginSuccess,this,&MyDialogManager::showWlecome);
}

void MyDialogManager::showWlecome(QString name)
{
     mainWorker();
     return;
    /*************上面为测试专用代码*******************************/
    login->close();
    welcome=new WelcomeDialog(name);
    welcome->show();
    dataManager=new DataManager(this);
    //发送信号开始准备
    QTimer::singleShot(0,dataManager,&DataManager::startInitData);

    connect(dataManager,&DataManager::getDataSuccess,[=](){
        qDebug()<<"loginSuccess and data has get";
        dataManager->saveJSON();
        emit workSig();
        //dataManager->killThread();

    });
}

void MyDialogManager::mainWorker()
{
    aimDialog=new AimDialog();
    aimDialog->show();
    //一定要在存在一个窗口时才能关闭另外一个窗口,
    //倘若一个窗口关闭,另一个窗口还没有show,那么QApplication就会立即quit,


    //测试专用代码
    return;
    /**


      */
    welcome->close();

    //将数据容器传给它
    aimDialog->setData(dataManager);
    //构造完成再初始化
    QTimer::singleShot(0,aimDialog,&AimDialog::initFun);

}
