#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QString>
#include<QWidget>

class Mylabel:public QLabel
{
    Q_OBJECT
public:
    Mylabel(QWidget *parent=0);
    ~Mylabel(){}
signals:
    void clicked();
protected:
    //过滤器
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYLABEL_H
