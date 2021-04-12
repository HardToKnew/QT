#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //future= new QFuture< void >;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    myEnable=1;
    //start(count);
    //if(future.isRunning())
        //future.
    //future=
    QtConcurrent::run(this,&MainWindow::xunhuan,count);//多线程执行死循环启动，可以带参数，具体格式可以查阅网上其它资料
    emit sig_num();
    count++;

}
void MainWindow::start(int c)//启动函数是需要在原有代码基础上增加
{


    QtConcurrent::run(this,&MainWindow::xunhuan,c);//传递参数


}

void MainWindow::xunhuan(int count)
{
    int i=0;
    int j=0;
    /*for (i=0;i<36384;i++)
    {
        for (j=0;j<46384;j++)
        {
            if( myEnable==0)
                break;
        }
        if( myEnable==0)
            break;
    }*/


    low[count]=i;
    upper[count]=j;
    qDebug()<<"ThreadID["<<i<<"]:"<<QThread::currentThreadId();
    qDebug()<<"low["<<count<<"]:"<<i<<"\t upper["<<count<<"]:"<<j<<"\n";

}

void MainWindow::on_pushButton_2_clicked()
{
    myEnable=0;
}
