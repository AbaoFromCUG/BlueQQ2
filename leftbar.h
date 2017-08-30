#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>
#include<QPixmap>
#include<QResizeEvent>
#include"popup.h"
namespace Ui {
class LeftBar;
}

class LeftBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftBar(QWidget *parent = 0);
    ~LeftBar();
    void setHead(QPixmap& );
    bool ab;

    bool avatorStatus;
    bool messageStatus;
    bool listStatus;
    bool settingStatus;
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::LeftBar *ui;
    Popup* pop;
    QPoint thisP;
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void barClicked(int num,bool status);

};

#endif // LEFTBAR_H
