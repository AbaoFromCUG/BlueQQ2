#include "ui_leftbar.h"
#include<QPainter>
#include"leftbar.h"
#include<QImage>
#include<QDebug>
#include<QResizeEvent>
#include"aimdialog.h"
LeftBar::LeftBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftBar)
{
    ab=true;
    ui->setupUi(this);
    pop=new Popup(this);
    connect(pop,&Popup::barClicked,[=](int num){
        switch (num) {
        case 0:
            //切换登录状态
            if(ab){
                ui->statusBar->setStyleSheet("background-color:#FFC24B;border-radius: 4px;");
            }else{
                ui->statusBar->setStyleSheet("background-color:rgb(121, 242, 47);border-radius: 4px;");
            }
            ab=!ab;
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    });

    avatorStatus=false;
    messageStatus=false;
    listStatus=false;
    settingStatus=false;
    QPixmap pix(":/images/demon/3.jpeg");
    setHead(pix);
    //头像的信号
    connect(ui->avator,&Mylabel::clicked,[=](){

        QPoint GlobalPoint(this->mapToGlobal(QPoint(0,0)));
        pop->setGeometry(GlobalPoint.x()+5,GlobalPoint.y()+50,110,140);
        pop->show();
        //如果头像已经被按下,那就
        if(avatorStatus){

        }else{
        }
    });
    //第一个消息图标的信号
    connect(ui->messageBar,&Mylabel::clicked,[=](){
        if(messageStatus){
            return;
        }else{
            listStatus=false;
            settingStatus=false;
            messageStatus=true;
            //如果按这里,且当前之前没有被按
            ui->listBar->setPixmap(QPixmap(":/images/widgets/friend1.png"));
            ui->settingBar->setPixmap(QPixmap(":/images/widgets/seting1.png"));
            ui->messageBar->setPixmap(QPixmap(":/images/widgets/message2.png"));
            emit barClicked(1,messageStatus);
        }

    });
    //列表图标的信号
    connect(ui->listBar,&Mylabel::clicked,[=](){
        if(listStatus){
            return;
        }else{
            settingStatus=false;
            messageStatus=false;
            listStatus=true;
            //如果按这里,且当前之前没有被按
            ui->listBar->setPixmap(QPixmap(":/images/widgets/friend2.png"));
            ui->settingBar->setPixmap(QPixmap(":/images/widgets/seting1.png"));
            ui->messageBar->setPixmap(QPixmap(":/images/widgets/message1.png"));
            emit barClicked(2,listStatus);
        }

    });
    //设置图标的信号
    connect(ui->settingBar,&Mylabel::clicked,[=](){
        if(settingStatus){
            return;
        }else{
            messageStatus=false;
            listStatus=false;
            settingStatus=true;
            //如果按这里,且当前之前没有被按
            ui->listBar->setPixmap(QPixmap(":/images/widgets/friend1.png"));
            ui->settingBar->setPixmap(QPixmap(":/images/widgets/seting2.png"));
            ui->messageBar->setPixmap(QPixmap(":/images/widgets/message1.png"));
            emit barClicked(3,settingStatus);
        }
    });

}

LeftBar::~LeftBar()
{
    delete ui;

}

void LeftBar::setHead(QPixmap & pix)
{

    ui->avator->setPixmap(AimDialog::getRoundImg(pix,40));
}

void LeftBar::resizeEvent(QResizeEvent *event)
{
    //thisP=QPoint(event->)
    pop->setGeometry(this->geometry().x(),this->geometry().y(),100,100);
}

void LeftBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
