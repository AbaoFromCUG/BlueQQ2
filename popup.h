#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class Popup;
}

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = 0);
    ~Popup();
    bool firstStatus;
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

private:
    Ui::Popup *ui;
signals:
    void barClicked(int num);

};

#endif // POPUP_H
