#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Dialog= new MyDialog;
    setMenus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setMenus()
{
    QMenu *FileMenu = menuBar()->addMenu(tr("&add"));
    QAction *add = new QAction(tr("&Open..."), this);
    FileMenu->addAction(add);
    connect(add,&QAction::triggered,Dialog, &MyDialog::show);
}
