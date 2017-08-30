#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QString naem,QWidget *parent = 0);
    ~WelcomeDialog();


private:
    Ui::WelcomeDialog *ui;
    QString name;

protected:
    void initUi();
};

#endif // WELCOMEDIALOG_H
