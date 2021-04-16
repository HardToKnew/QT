#include "mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    addressWidget = new TableWidget;
    //addressWidget->setupTab();
    //this->setCentralWidget(addressWidget);
   /* QBoxLayout *main=new QHBoxLayout();
    this ->setLayout(main);
    main->addWidget(addressWidget,0);*/
}

MainWindow::~MainWindow()
{
}

