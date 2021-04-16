#include "mainwindow.h"
#include "ui_mainwindows.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    addressWidget = new TableWidget(this);
    //addressWidget->setupTab(this);
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
    connect(add,&QAction::triggered,addressWidget, &TableWidget::showAddEntryDialog);
}

