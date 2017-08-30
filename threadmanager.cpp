#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) : QObject(parent)
{

}

void ThreadManager::addToManager(QThread *thread)
{
    list.append(thread);

}

ThreadManager::~ThreadManager()
{
    for(int i=0;i<list.length();i++){
        if(list[i]->isRunning()){
            list[i]->quit();
        }
    }
}
