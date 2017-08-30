#include<QLabel>
#include"mylabel.h"

Mylabel::Mylabel(QWidget* parent)
    :QLabel(parent)
{

}

void Mylabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
