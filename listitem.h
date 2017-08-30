#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include<QResizeEvent>

namespace Ui {
class ListItem;
}

class ListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListItem(QWidget *parent,QString src,QString name,QString mess,QString u);
    ~ListItem();
    void setType(int value);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);


    QString imgSrc;
private:
    Ui::ListItem *ui;
    QString uin;
    int type;
signals:
    void clicked(int num,QString uin,int type);
};

#endif // LISTITEM_H

