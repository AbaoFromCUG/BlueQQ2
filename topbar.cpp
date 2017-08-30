#include "topbar.h"
#include "ui_topbar.h"
#include<QPainter>
#include<QDebug>
#include<QIcon>
#include<QPaintEvent>
TopBar::TopBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopBar)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    normalStatus=true;
}

TopBar::~TopBar()
{
    delete ui;
}

void TopBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TopBar::resizeEvent(QResizeEvent *event)
{
    int pWidth=event->size().width();
    int pHeight=event->size().height();
    int btnW=47;
    int btnH=32;
    ui->closeBtn->setGeometry(pWidth-btnW,0,btnW,btnH);
    ui->maxBtn->setGeometry(pWidth-2*btnW,0,btnW,btnH);
    ui->minBtn->setGeometry(pWidth-3*btnW,0,btnW,btnH);


}


void TopBar::on_minBtn_clicked()
{
    qDebug()<<"min clicked";
    emit barClicked(0);
}


void TopBar::on_maxBtn_clicked()
{
    //翻转图标
    if(!normalStatus){
        ui->maxBtn->setIcon(QIcon(":/images/widgets/max.png"));
    }else {
        ui->maxBtn->setIcon(QIcon(":/images/widgets/normal.png"));
    }
    ui->maxBtn->setIconSize(QSize(40,32));
    normalStatus=!normalStatus;
    emit barClicked(1);
}
void TopBar::on_closeBtn_clicked()
{
    emit barClicked(2);
}
