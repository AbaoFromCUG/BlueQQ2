#include "groupbar.h"
#include "ui_groupbar.h"
#include<QResizeEvent>
#include<QPainter>
GroupBar::GroupBar(QWidget *parent,QString u,QString name,QString s) :
    QWidget(parent),
    ui(new Ui::GroupBar)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->status->setText(s);
    this->uin=u;

    //初始化没有折叠
    status=false;

}

GroupBar::~GroupBar()
{
    delete ui;
}

QString GroupBar::getStatusText()
{
    return ui->status->text();
}

QString GroupBar::getUin()
{
    return this->uin;
}

void GroupBar::setStatusText(QString str)
{
    ui->status->setText(str);
}

void GroupBar::resizeEvent(QResizeEvent *event)
{
    QSize size=event->size();
    ui->name->setGeometry(40,8,size.width()-110,20);
    ui->status->setGeometry(size.width()-60,8,50,20);

}

void GroupBar::mousePressEvent(QMouseEvent *event)
{
    if(!status){
        ui->ico->setPixmap(QPixmap(":/images/widgets/triangle2.png"));
    }else {
        ui->ico->setPixmap(QPixmap(":/images/widgets/triangle1.png"));
    }
    status=!status;

    emit clicked(status);
}

void GroupBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
