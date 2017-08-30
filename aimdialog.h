#ifndef AIMDIALOG_H
#define AIMDIALOG_H

#include <QDialog>
#include<QWidget>
#include<QPixmap>
#include<QTreeWidgetItem>
#include<QDebug>
#include<QResizeEvent>
#include<QSize>
#include<QPainter>
#include<QTreeWidgetItem>
#include<QByteArray>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"listitem.h"
#include"groupbar.h"
#include"datamanager.h"
#include"lib/framelesshelper.h"
struct oneMessage{
    QString uin;
    QString name;
    QString mess;
    QString imgSrc;
};

namespace Ui {
class AimDialog;
}

class AimDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AimDialog(QWidget *parent = 0);
    ~AimDialog();

    void setData(DataManager* manager);
public slots:
    void initFun();
    void showChange(int status);


    static QPixmap getRoundImg(QPixmap& pix,int r);
protected:
    void initTop();
    void initLeft();
    void initListBar();
    void initTalkView();
    void initMessageList();
    //监听鼠标在窗口内的时间
    void mousePressEvent(QMouseEvent *event);  //按下事件
    void mouseMoveEvent(QMouseEvent *event);   //移动事件
    void mouseDoubleClickEvent(QMouseEvent *event);     //双击事件
    void mouseReleaseEvent(QMouseEvent* event);     //释放事件


public slots:
    //正式开始生成各种列表
    void initGroupList();  //群列表
    void initDissList();   //讨论组列表
    void initCategories(); //好友组bar
    void initFriendList(); //将每个好友都添加到各自分组里





    void addTopItem(QString uin,QString name,QString status);
    void addItem(QTreeWidgetItem* rootItem, oneMessage data,int t);

    /*
     * 这里写一个功能函数,向一个分组里(包括讨论组,群列表,好友分组加一个item)
     * 0表示群列表,1表示讨论组,然后,其他的通过遍历搜索
     * n叉树?
     * 两个方法,分别是
     * setItemWidget
     * ItemWidget
     *
     */
    void add(int num, oneMessage one);



    void resizeEvent(QResizeEvent *);
private:
    Ui::AimDialog *ui;
    DataManager* data;
    bool mouseMove;
    QPoint m_moveStart;
    FramelessHelper* helper;
    int showWhich;

};

#endif // AIMDIALOG_H
