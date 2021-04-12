#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtConcurrent>//要记得添加该头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start(int);//多线程启动函数，在原有的代码基础上增加该函数
    void xunhuan(int );//死循环函数，用这个函数代替原有代码的函数

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
     QFuture < void > future;
    int myEnable=0;//标志位，用于退出死循环操作
    QString threadText;

signals:
    void sig_num(int );
};
#endif // MAINWINDOW_H
