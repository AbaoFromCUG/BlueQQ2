#include "popup.h"
#include "ui_popup.h"
#include<QPainter>
Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    //屏幕边框消失
    setWindowFlags(Qt::FramelessWindowHint  |Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground, true);
    firstStatus=false;

}

Popup::~Popup()
{
    delete ui;
}

void Popup::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Popup::on_btn1_clicked()
{
    if(firstStatus){

        ui->widget->setStyleSheet("background-color:#FFC24B;border-radius: 4px;");
        ui->btn1->setText("隐身");
    }else{
        ui->widget->setStyleSheet("background-color:rgb(121, 242, 47);border-radius: 4px;");
        ui->btn1->setText("在线");
    }
    firstStatus=!firstStatus;
    emit barClicked(0);
    close();
}

void Popup::on_btn2_clicked()
{
    emit barClicked(1);
    close();
}

void Popup::on_btn3_clicked()
{

    emit barClicked(2);
    close();
}
