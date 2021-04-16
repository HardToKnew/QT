#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,Ui(new ui::MainWindow)
{
   //Ui->setupUI(this);
    Ui_ROIDetails *ui=new Ui_ROIDetails;
    setCentralWidget(ui);
}

MainWindow::~MainWindow()
{
}

