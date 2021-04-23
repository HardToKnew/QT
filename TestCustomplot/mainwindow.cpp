#include "mainwindow.h"
#include <QBoxLayout>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget=new QWidget(this);





    customPlot = new QCustomPlot(centralWidget);

    QBoxLayout *verticalLayout=new QVBoxLayout(centralWidget);
    verticalLayout->addWidget(customPlot);
    this->setCentralWidget(centralWidget);
     //contextMenuRequest(QPoint(20.0,20.0));

    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, &QWidget::customContextMenuRequested, this, &MainWindow::contextMenuRequest);
    //connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}
void MainWindow::contextMenuRequest(QPoint pos)
{
    std::cout<<"pos:"<<pos.x()<<std::endl;
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
      menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
      menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
      menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
      menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
      menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    } else  // general context menu on graphs requested
    {
      menu->addAction("Add random graph");
      if (customPlot->selectedGraphs().size() > 0)
        ;//menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
      if (customPlot->graphCount() > 0)
       ;// menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
    }

    menu->popup(customPlot->mapToGlobal(pos));
}

MainWindow::~MainWindow()
{
}

