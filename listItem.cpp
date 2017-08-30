#include "listitem.h"
#include "ui_listitem.h"
#include"aimdialog.h"
#include<QPainter>
ListItem::ListItem(QWidget *parent, QString src, QString name, QString mess,QString u) :
    QWidget(parent),
    ui(new Ui::ListItem)
{
    ui->setupUi(this);
    this->imgSrc=src;
    this->uin=u;

    ui->name->setText(name);
    ui->message->setText(mess);
    QPixmap pix(imgSrc);
    ui->avatar->setPixmap(AimDialog::getRoundImg(pix,40));
    connect(ui->avatar,&Mylabel::clicked,[=](){
        emit clicked(0,uin,type);
    });


}



ListItem::~ListItem()
{
    delete ui;
}

void ListItem::setType(int value)
{
    type=value;
}

void ListItem::resizeEvent(QResizeEvent *event)
{
    QSize size=event->size();
    ui->name->setGeometry(60,5,size.width()-60,30);
    ui->message->setGeometry(60,28,width()-60,18);

}

void ListItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ListItem::mousePressEvent(QMouseEvent *event)
{
    emit clicked(1,uin,type);
}
