#include "worker.h"

Worker::Worker(QObject *parent)
    :QObject(parent)
{
    qDebug()<<"worker()";
}
Worker::~Worker()
{
    qDebug()<<"~worker()";
}
void Worker::slot_dowork()
{
    for(int i=0;i<56384;i++)
    {
        for(int i=0;i<56384;i++)
        {

        }
    }
    qDebug()<< "do work,thread id = " << QThread::currentThreadId();
    emit sig_finish();
}

