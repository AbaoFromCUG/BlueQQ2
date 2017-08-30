#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include<QThread>
#include<QList>

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = nullptr);
    void addToManager(QThread* thread);
    ~ThreadManager();

private:
    QList<QThread*> list;
signals:

public slots:
};

#endif // THREADMANAGER_H
