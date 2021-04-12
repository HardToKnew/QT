#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>


class Worker:public QObject
{
    Q_OBJECT
public:
    Worker(QObject *parent=0);
    ~Worker();
signals:
    void sig_finish(QString);

public slots:
    void slot_dowork();
};

#endif // WORKER_H
