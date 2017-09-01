#include "talkview.h"
#include "ui_talkview.h"

#include"mynetworker.h"
TalkView::TalkView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalkView)
{
    ui->setupUi(this);
    //信号槽
    connect(ui->backBar,&Mylabel::clicked,[=](){
        barClicked(0);
    });
    connect(ui->friendName,&Mylabel::clicked,[=](){
        barClicked(1);
    });
    connect(ui->menuBar,&Mylabel::clicked,[=](){
        barClicked(2);
    });
}

TalkView::~TalkView()
{
    delete ui;
}

void TalkView::resizeEvent(QResizeEvent *event)
{
    QSize mainSize=event->size();
    ui->textEdit->setGeometry(0,mainSize.height()-110,mainSize.width(),110);
    ui->phizBar->setGeometry(15,mainSize.height()-140,20,20);
    ui->imgBar->setGeometry(50,mainSize.height()-140,20,20);
    ui->timeBar->setGeometry(85,mainSize.height()-140,20,20);
    ui->bubbleList->setGeometry(0,40,mainSize.width(),mainSize.height()-190);
    ui->sendButton->setGeometry(mainSize.width()-70,mainSize.height()-143,60,26);
    ui->friendName->setGeometry(50,10,mainSize.width()-100,20);
    ui->menuBar->setGeometry(mainSize.width()-44,7,26,26);
}

QList<MessageItem *> TalkView::getList(ChatMessageInfoList *list)
{

}

void TalkView::on_sendButton_clicked()
{
    QString text=ui->textEdit->toPlainText();
    switch (type) {
    case 0:
        messager->sendMessageToGroup(aimUin,text);
        break;
    case 1:
        messager->sendMessageToGroup(aimUin,text);
        break;
    case 2:
        messager->sendMeeageToFriend(aimUin,text);
        break;
    default:
        break;
    }
}

void TalkView::showMessage(QList<MessageItem*> list)
{

    QQmlContext *ctxt = ui->bubbleList->rootContext();
    ctxt->setContextProperty("myModel", QVariant::fromValue(list));

    QUrl source("qrc:/BubbleList.qml");
    ui->bubbleList->setSource(source);

}

void TalkView::setData(DataManager *value,MessageManager* messager)
{
    data = value;
    this->messager=messager;
    messager->setDataManager(value);
}

void TalkView::setAimUin(const QString &value, int type)
{
    aimUin = value;
    this->type=type;
    switch (type) {
    case 0:
        ui->friendName->setText(data->getGroupXByUin("name",value));

        break;
    case 1:
        ui->friendName->setText(data->getDissXByUin("name",value));
        break;
    default:
        if(data->getFriendXByUin("markname",value)!=""){
            ui->friendName->setText(data->getFriendXByUin("markname",value));
        }else if(data->getFriendXByUin("nick",value)!=""){
            ui->friendName->setText(data->getFriendXByUin("nick",value));
        }
        break;
    }


    //messager->getMessageListByUin(aimUin);

}

