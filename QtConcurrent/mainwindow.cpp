#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,&MainWindow::sig_num,this,&MainWindow::start);
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{

    myEnable=1;
    qDebug()<<"startThreadID"<<QThread::currentThreadId();
    threadText = "Thread:"+ui->lineEdit->text()+"\nstartThreadID:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'));
    emit sig_num(ui->lineEdit->text().toInt());
    ui->textEdit->setText(threadText);
    //count++;

}
void MainWindow::start(int c)//启动函数是需要在原有代码基础上增加
{

    for(int i=0;i<c;i++){

        QtConcurrent::run(this,&MainWindow::xunhuan,i);//传递参数
    }


}

void MainWindow::xunhuan(int count)
{

    while (myEnable) {


    }
    qDebug()<<"ThreadID["<<count<<"]:"<<QThread::currentThreadId();
    threadText = threadText+"\n"+"ThreadID["+QString::number(count,10)+"]:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'));


}

void MainWindow::on_pushButton_2_clicked()
{
    myEnable=0;
    qDebug()<<"stopThreadID"<<QThread::currentThreadId();
    for (int i=0;i<1000;i++) {
        for (int i=0;i<1000;i++) {


        }


    }
    threadText = threadText+"\nstopThreadID:"+QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 4, 16, QLatin1Char('0'));

    ui->textEdit->setText(threadText);
    //threadText="";
}

