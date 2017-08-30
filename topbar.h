#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

namespace Ui {
class TopBar;
}

class TopBar : public QWidget
{
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = 0);
    ~TopBar();
    bool normalStatus;
private:
    Ui::TopBar *ui;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
public slots:
    void on_minBtn_clicked();
    void on_closeBtn_clicked();
    void on_maxBtn_clicked();
signals:
    void barClicked(int num);
};

#endif // TOPBAR_H
