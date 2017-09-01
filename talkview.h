#ifndef TALKVIEW_H
#define TALKVIEW_H

#include <QWidget>
#include<QList>
#include<QQuickItem>
#include<QQuickView>
#include<QVariant>
#include<QQmlContext>
#include"message/messageitem.h"
#include<datamanager.h>
#include"message/messagemanager.h"
#include"message/chatmessageinfo.h"
namespace Ui {
class TalkView;
}

class TalkView : public QWidget
{
    Q_OBJECT

public:
    explicit TalkView(QWidget *parent = 0);

    ~TalkView();
    void setAimUin(const QString &value,int type);

    void setData(DataManager *value, MessageManager *messager);

public slots:
    void showMessage(QList<MessageItem *> list);
protected:
    void resizeEvent(QResizeEvent *event);
    QList<MessageItem*> getList(ChatMessageInfoList* list);

private slots:
    void on_sendButton_clicked();


private:
    Ui::TalkView *ui;
    QString aimUin;
    DataManager* data;
    MessageManager* messager;
    int type;
signals:
    /*
     * 0表示左上角的返回被按下
     * 1表示上面的昵称被按下
     * 2表示右上的菜单被按下
     *
    */
    void barClicked(int num);
};

#endif // TALKVIEW_H
