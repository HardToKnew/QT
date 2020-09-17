#include "mainwindow.h"
#include "chartview.h"
#include <iostream>
#include <QBoxLayout>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chartview *mainview = new chartview(this);
    setCentralWidget(mainview);
}

MainWindow::~MainWindow()
{

}

/*void MainWindow::mousePressEvent(QMouseEvent *event)
{

    //if(event->button() == Qt::LeftButton){
      // int data = event->pos().x();//chart-> mapToValue(event->pos()).x();
       cout<<"data111:"<</*data<<*//*endl;
    //}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{



}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}*/
