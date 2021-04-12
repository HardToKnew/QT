#include "worker.h"

Worker::Worker(QObject *parent)
    :QObject(parent)
{
   // qDebug()<<"worker()";
}
Worker::~Worker()
{
    qDebug()<<"~worker()";
}
void Worker::slot_dowork()
{

    //qDebug()<< "do work,thread id = " << QThread::currentThreadId();
    QString buf="do work thread id:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'))+"\n";
    emit sig_finish(buf);
}

