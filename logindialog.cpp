#include "logindialog.h"
#include "ui_logindialog.h"
#include<QIcon>
#include<QDebug>
#include<QPixmap>
#include"loginnetworkmanager.h"
#include"mynetworkcookiejar.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    manager=new LoginNetWorkManager(this);
    manager->needNewQR();
    initUi();
    initLogic();
    /*
    login_help=new FramelessHelper(this);
    login_help->activateOn(this);  //激活当前窗体
    login_help->setTitleHeight(0);  //设置窗体的标题栏高度
    login_help->setWidgetMovable(true);  //设置窗体可移动
    login_help->setWidgetResizable(true);  //设置窗体可缩放
    login_help->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    login_help->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

    */

}

LoginDialog::~LoginDialog()
{
    delete ui;
}
//初始化UI代码
void LoginDialog::initUi()
{
    login_button=new QPushButton(this);
    QIcon login_button_bg(":/images/login/login_button_naive.png");
    login_button->setIcon(login_button_bg);
    login_button->setIconSize(QSize(128,83));
    login_button->setGeometry(QRect(203,200,128,83));
    login_button->setFlat(true);
}
//初始化逻辑代码
void LoginDialog::initLogic()
{
    //各种信号槽的连接
    connect(login_button,SIGNAL(clicked()),this,SLOT(buttonClick()));
    connect(login_button,&QPushButton::pressed,[this](){
        this->login_button->setIcon(QIcon(":/images/login/login_button_click.png"));
    });
    connect(login_button,&QPushButton::released,[this](){
        this->login_button->setIcon(QIcon(":/images/login/login_button_naive.png"));
    });

    connect(manager,&LoginNetWorkManager::getPix,[this](QPixmap& newPix){
        this->ui->label->setPixmap(newPix);
    });
    connect(manager,&LoginNetWorkManager::loginSuccess,[this](QString name){
       //抓取下层信号,发送到上层
        emit loginSuccess(name);
    });

}

void LoginDialog::buttonClick()
{
    qDebug()<<"onclick";
    emit loginSuccess("test");

}

