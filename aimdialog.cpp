#include "aimdialog.h"
#include "ui_aimdialog.h"

AimDialog::AimDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AimDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    initTop();
    initLeft();
    initListBar();
    initTalkView();

    //初始化显示两个
    showWhich=0;
    //窗口助手
    helper=new FramelessHelper(this);
    helper->activateOn(this);  //激活当前窗体
    helper->setTitleHeight(ui->topBar->height());  //设置窗体的标题栏高度
    helper->setWidgetMovable(true);  //设置窗体可移动
    helper->setWidgetResizable(true);  //设置窗体可缩放
    helper->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    helper->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放


}

AimDialog::~AimDialog()
{
    delete ui;
}

void AimDialog::setData(DataManager *manager)
{
    this->data=manager;
    //同时将talkView的data设置为mannager共享数据源
    ui->talkView->setData(manager);

}

QPixmap AimDialog::getRoundImg(QPixmap &pix, int r)
{
    //采用图片混合透视的方式获得圆形切图。
    QImage resultImage(QSize(r,r),QImage::Format_ARGB32_Premultiplied);
    //加载遮罩图
    QPixmap mask(":/images/widgets/round.png");
    //因为我的遮罩是160*160的,所以要放缩
    mask=mask.scaled(QSize(r,r));
    //以resultImage作为画板,
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOut);

    painter.drawPixmap(0, 0, pix.scaled(QSize(r,r)));

    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

    painter.end();
    return QPixmap::fromImage(resultImage);


}

void AimDialog::initFun()
{
    initGroupList();
    initDissList();
    initCategories();
    initFriendList();
}

void AimDialog::showChange(int status)
{
    showWhich=status;
    switch (showWhich) {
    case 0:
        ui->listWidget->show();
        ui->talkView->show();
        return;
        break;
    case 1:
        ui->listWidget->show();
        ui->talkView->hide();
        break;
    case 2:
        ui->listWidget->hide();
        ui->talkView->show();
        break;
    default:

        break;
    }
}

void AimDialog::initTop()
{
    connect(ui->topBar,&TopBar::barClicked,[=](int num){
        switch (num) {
        case 0:
            showMinimized();
            break;
        case 1:
            if(!ui->topBar->normalStatus){
                showFullScreen();
            }else {
                showNormal();
            }
            break;
        case 2:
            close();
            break;
        default:
            break;
        }

    });

}

void AimDialog::initLeft()
{

}

void AimDialog::initListBar()
{
    //好友列表bar的初始化
    QTreeWidget* the=ui->listWidget;
    the->clear();
    the->setColumnCount(1);
    //设置复选框宽度为0
    the->setIndentation(0);
    the->setHeaderHidden(true);


    //群列表bar
    addTopItem("0","我的群","0");
    //讨论组bar
    addTopItem("1","我的讨论组","0");

    //添加一个窄窄的分割线
    QTreeWidgetItem* line=new QTreeWidgetItem(the);
    line->setFlags(Qt::ItemIsSelectable);
    QWidget* widget=new QWidget(the);
    widget->setStyleSheet("background-color:#000000");
    the->setItemWidget(line,0,widget);
    QRect rect(line->treeWidget()->visualItemRect(line));
    line->setSizeHint(0,QSize(rect.width(),2));



}

void AimDialog::initGroupList()
{
    QJsonArray groupArray=data->groupList.value("gnamelist").toArray();
    /*
     * {
     *      "code": 2901344025,
     *      "flag": 1090520065,
     *      "gid": 2917135826,
     *      "name": "abcd1234"
     *  }
     */
    for(int i=0;i<groupArray.count();i++){
        QJsonObject itemObeject=groupArray[i].toObject();
        oneMessage mess{
            QString::number((long long)itemObeject.value("gid").toDouble()),
            itemObeject.value("name").toString(),
            "",
            ":/images/demon/group1.jpg"
        };
        add(0,mess);
    }
}

void AimDialog::initDissList()
{
    QJsonArray dissArray=data->discusList.value("dnamelist").toArray();
    /*
     * {
     *       "did": 3227493853,
     *       "name": "墨飞云、💤、刺猬鸟"
     * }
     */

    for(int i=0;i<dissArray.count();i++){
        QJsonObject itemObject=dissArray[i].toObject();
        oneMessage mess{
            QString::number((long long)itemObject.value("did").toDouble()),
            itemObject.value("name").toString(),
            "",
            ":/images/demon/group2.jpg"
        };
        add(1,mess);
    }
}
//添加所有分组
void AimDialog::initCategories(){
    QJsonArray objectArray=data->friendList.value("categories").toArray();
    if(objectArray[0].toObject().value("index")==1){
        //如果分组的序列第一个是1,则表示有一个默认分组(分组名称为我的好友)
        addTopItem("0","我的好友","0/0");
    }
    /*
     * {
     *      "index": 1,
     *       "name": "分组3",
     *      "sort": 2
     *  },
     */
    for(int index=0;index<objectArray.count();index++){
        QJsonObject obj=objectArray[index].toObject();
        addTopItem(QString::number(obj.value("index").toInt()),obj.value("name").toString(),"0/0");
    }
}

void AimDialog::initFriendList()
{
    QJsonArray friendlist=data->friendList.value("friends").toArray();
    for(auto i: friendlist){
        QJsonObject obj=i.toObject();
        int index=obj.value("categories").toInt();
        QString uin=QString::number((long long)obj.value("uin").toDouble());
        //应为前面还有群bar和讨论组bar以及分割线,所以加三
        index+=3;
        QString markName=data->getFriendXByUin("markname",uin);
        //如果没有备注
        if(markName==""){
            //将个人昵称设为显示的备注
            markName=data->getFriendXByUin("nick",uin);
        }
        oneMessage message{
            uin,markName,"",":/images/demon/selfImg.jpg"
        };
        add(index,message);
    }
}

void AimDialog::addTopItem(QString uin,QString name,QString status)
{
    //群的bar,编号为0
    QTreeWidgetItem *TopBar=new QTreeWidgetItem(ui->listWidget);
    TopBar->setFlags(Qt::ItemIsSelectable);
    GroupBar* g=new GroupBar(ui->listWidget,uin,name,status);
    //顶级bar点击事件,展开或收起
    connect(g,&GroupBar::clicked,[=](bool status){
        status?(ui->listWidget->expandItem(TopBar)):(ui->listWidget->collapseItem(TopBar));
    });
    ui->listWidget->setItemWidget(TopBar,0,g);
}

void AimDialog::initTalkView()
{
    connect(ui->talkView,&TalkView::barClicked,[=](int num){
        /*
         * 0表示左上角的返回被按下
         * 1表示上面的昵称被按下
         * 2表示右上的菜单被按下
         *
        */
        switch (num) {
        case 0:
            if(showWhich==2){
                showChange(1);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    });
}

void AimDialog::initMessageList()
{

}
/*
 *   int btnW=47;
 *   int btnH=32;
 */
void AimDialog::mousePressEvent(QMouseEvent *event)
{
    if(0){

    }else if(event->globalX()<this->x()+ui->topBar->width()-47*3&&event->globalY()<this->y()+32){
        //标题栏拖动
        m_moveStart=event->globalPos();
        mouseMove=true;
        qDebug()<<"mousePress";
    }

    return QWidget::mousePressEvent(event);
}

void AimDialog::mouseMoveEvent(QMouseEvent *event)
{

    if(event->globalX()<this->x()+ui->topBar->width()-47*3&&event->globalY()<this->y()+32){
        if(mouseMove){
            QPoint moveP(event->globalX()-m_moveStart.x(),event->globalY()-m_moveStart.y());
            this->move(moveP+this->pos());
            m_moveStart=event->globalPos();
            qDebug()<<"mouseMove";
        }
    }

    return QWidget::mouseMoveEvent(event);
}

void AimDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"mouseDoubleClick";
    QPoint localPoint=QPoint(event->globalX()-this->x(),event->globalY()-this->y());
    if(localPoint.x()<this->width()-47*3&&localPoint.y()<32){
        ui->topBar->on_maxBtn_clicked();
    }
    return QWidget::mouseDoubleClickEvent(event);
}

void AimDialog::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->globalX()<this->x()+ui->topBar->width()-47*3&&event->globalY()<this->y()+32){
        mouseMove=false;
    }
    return QWidget::mouseReleaseEvent(event);
}

void AimDialog::addItem(QTreeWidgetItem *rootItem, oneMessage data,int t)
{
    QTreeWidgetItem* wid=new QTreeWidgetItem(rootItem);
    ListItem* item=new ListItem(ui->listWidget,data.imgSrc,data.name,data.mess,data.uin);
    item->setType(t);
    ui->listWidget->setItemWidget(wid,0,item);
    connect(item,&ListItem::clicked,[=](int num,QString uin,int type){
        switch (num) {
        //头像
        case 0:

            break;
            //其他地方被按下,开始聊天
        case 1:
            if(showWhich==1)
                 showChange(2);
            ui->talkView->setAimUin(uin,type);



            break;
        default:
            break;
        }
    });
    QRect rect(rootItem->treeWidget()->visualItemRect(rootItem));
    wid->setSizeHint(0,QSize(rect.width(),50));
}



void AimDialog::add(int num, oneMessage one)
{
    //群,讨论组

    QTreeWidgetItem* zu= ui->listWidget->topLevelItem(num);
    addItem(zu,one,num);
    GroupBar *bar=(GroupBar*)ui->listWidget->itemWidget(zu,0);
    int status=bar->getStatusText().toInt();
    bar->setStatusText(QString::number(status+1));




}




void AimDialog::resizeEvent(QResizeEvent *event)
{
    QSize newSize=event->size();
    ui->topBar->setGeometry(0,0,newSize.width(),32);
    QSize topSize=QSize(ui->topBar->width(),ui->topBar->height());
    ui->leftBar->setGeometry(0,topSize.height(),50,newSize.height()-topSize.height());
    QSize leftSize=ui->leftBar->size();
    QSize otherSize=QSize(newSize.width()-leftSize.width(),newSize.height()-topSize.height());
    if(otherSize.width()<490){
        ui->talkView->setGeometry(leftSize.width(),ui->topBar->height(),newSize.width()-leftSize.width(),newSize.height()-topSize.height());
        ui->listWidget->setGeometry(leftSize.width(),ui->topBar->height(),newSize.width()-leftSize.width(),newSize.height()-topSize.height());


        //在这里需要判定一下哪个是活动的,但是暂时做不到
        showChange(1);

    }else {

        showChange(0);
        //丈量分地左侧列表区域最小宽度和最大宽度
        //
        int listMinW=250;
        int listMaxW=400;
        int listW=listMinW+(otherSize.width()-490)*0.3;
        if(listW>listMaxW)
            listW=listMaxW;
        ui->listWidget->setGeometry(leftSize.width(),ui->topBar->height(),listW,newSize.height()-topSize.height());
        ui->talkView->setGeometry(leftSize.width()+listW,ui->topBar->height(),newSize.width()-leftSize.width()-listW,newSize.height()-topSize.height());


    }


    QSize listSize=ui->listWidget->size();

}
