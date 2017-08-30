#include "welcomedialog.h"
#include "ui_welcomedialog.h"
#include<QMovie>
#include<QPixmap>
#include<QLabel>
WelcomeDialog::WelcomeDialog(QString naem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog),
    name(naem)
{
    initUi();


}


WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}


void WelcomeDialog::initUi()
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QMovie * movie=new QMovie(":/images/welcome/over.gif");
    ui->label->setMovie(movie);
    movie->setScaledSize(QSize(350,622));
    movie->start();
    connect(movie,&QMovie::finished,[this](){
        QPixmap* pix=new QPixmap(":/images/welcome/bg.png");
        ui->label->setPixmap(*pix);
        QLabel* welLabel=new QLabel(this);
        QString text=QString("<center><h1>你好啊</h1></center><center><h1>%1</h1><center><center><h4>我针对你进行了一些优化</h4></center>").arg(name);
        welLabel->setText(text);
        welLabel->setGeometry(10,40,340,400);
        welLabel->show();

    });
}
