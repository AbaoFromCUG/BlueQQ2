#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QPushButton>
#include"loginnetworkmanager.h"
#include<QPixmap>
#include"lib/framelesshelper.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    void initUi();
    void initLogic();
    QPushButton *login_button;
    LoginNetWorkManager* manager;
    FramelessHelper *login_help;
protected slots:
    void buttonClick();

signals:
    //向上级发送的信号
    void loginSuccess(QString);
};

#endif // LOGINDIALOG_H
