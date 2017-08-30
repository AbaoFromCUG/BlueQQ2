#ifndef GROUPBAR_H
#define GROUPBAR_H

#include <QWidget>

namespace Ui {
class GroupBar;
}

class GroupBar : public QWidget
{
    Q_OBJECT

public:
    explicit GroupBar(QWidget *parent,QString u,QString name,QString s);
    ~GroupBar();
    bool status;
    QString getStatusText();
    QString getUin();
    void setStatusText(QString str);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    Ui::GroupBar *ui;
    QString uin;

signals:
    void clicked(bool);
};

#endif // GROUPBAR_H
