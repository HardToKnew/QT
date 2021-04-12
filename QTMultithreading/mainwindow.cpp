#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_pworker = new Worker();
    m_pthread = new QThread();
    m_pworker->moveToThread(m_pthread);
    threadText = "UIThread:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'))+"\n";
    //qDebug()<< "start,thread id = " << QThread::currentThreadId();

    connect(m_pthread, &QThread::finished, m_pworker, &QObject::deleteLater);
    connect(this,SIGNAL(sig_dowork()),m_pworker,SLOT(slot_dowork()));
    connect(m_pworker,&Worker::sig_finish,this,&MainWindow::slot_finish);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_pthread->quit();
    m_pthread->wait();
}

void MainWindow::dowork()
{
    m_pthread->start();
    emit sig_dowork();
}

void MainWindow::slot_finish(QString buf)
{
     //qDebug()<< "finish,thread id = " << QThread::currentThreadId();
    threadText =threadText+buf+"finishThread:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'))+"\n\n";
    ui->textEdit->setText(threadText);
}


void MainWindow::on_pushButton_clicked()
{
    threadText = threadText+"startThread:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'))+"\n";
    m_pthread->start();
    emit sig_dowork();
}
