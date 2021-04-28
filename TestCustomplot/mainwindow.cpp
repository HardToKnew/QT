#include "mainwindow.h"
#include <QBoxLayout>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setToolBar(this);
    centralWidget=new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->resize(600,400);

    customPlot = new QCustomPlot(centralWidget);
    customPlot->xAxis->setRange(-10, 10);
    customPlot->yAxis->setRange(0, 15);
    customPlot->setInteractions(/*QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes |
                                      QCP::iSelectLegend |*/ QCP::iSelectPlottables);// 设置相应的枚举量选中图表
    //customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);


    textEdit = new QTextEdit(centralWidget);

    QBoxLayout *verticalLayout=new QVBoxLayout(centralWidget);
    verticalLayout->addWidget(customPlot,4);
    verticalLayout->addWidget(textEdit,1);

    setupDemo(customPlot);





    connect(customPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::selectionChanged);
    //connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));

    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);//开启QWidget::customContextMenuRequested信号
    connect(customPlot, &QWidget::customContextMenuRequested, this, &MainWindow::contextMenuRequest);
    //connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

    connect(customPlot, &QCustomPlot::plottableClick, this,&MainWindow::graphClicked);


}
void MainWindow::setToolBar(QMainWindow *mainWindow)
{
    QToolBar *toolBar = new QToolBar(mainWindow);
    mainWindow->addToolBar(toolBar);
    selectQAc = new QAction(tr("框选"),toolBar);
    toolBar->addAction(selectQAc);
    selectQAc->setCheckable(true);
    selectQAc->setChecked(false);
    connect(selectQAc,&QAction::toggled,this,&MainWindow::selectToggle);


}
void MainWindow::setupDemo(QCustomPlot *customPlot)
{
    mGraph=customPlot->addGraph();//setSelectionRectMode(QCP::srmSelect);
    customPlot->graph();
    QColor color(0,0, 255);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color.lighter(200)));
    //customPlot->graph()->setBrush(QBrush(color));
    // generate random walk data:
    QVector<QCPGraphData> timeData(200);
    for (int i=0; i<200; ++i)
    {
      timeData[i].key = -10+0.1*i+(1.0*rand()/(RAND_MAX+1.0));
      timeData[i].value =exp(0.016*i)+(1.0*rand()/(RAND_MAX+1.0));
    }
    customPlot->graph()->data()->set(timeData);

    QPen graphPen;
    graphPen.setColor(QColor(0,128,0));
    graphPen.setWidthF(1);
    customPlot->graph()->setPen(graphPen);
  //}
  // show legend with slightly transparent background brush:
  customPlot->legend->setVisible(true);
  customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}
void MainWindow::contextMenuRequest(QPoint pos)
{
    //std::cout<<"pos:"<<pos.x()<<std::endl;
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
      menu->addAction("Add random graph", this, &MainWindow::addRandomGraph);
      if (customPlot->selectedGraphs().size() > 0)
        menu->addAction("Remove selected graph", this, &MainWindow::removeSelectedGraph);
      if (customPlot->graphCount() > 0)
        menu->addAction("Remove all graphs", this, &MainWindow::removeAllGraphs);
    }

    menu->popup(customPlot->mapToGlobal(pos));
}
void MainWindow::addRandomGraph()
{
    bool ok;
    double start=0,end=10;
    QString X = QInputDialog::getText(this, "QCustomPlot example", "x:", QLineEdit::Normal, "0", &ok);
    if (ok)
    {
      //axis->setLabel(newLabel);
      //ui->customPlot->replot();
        start=X.toDouble();
    }
    QString Y = QInputDialog::getText(this, "QCustomPlot example", "y:", QLineEdit::Normal, "10", &ok);
    if (ok)
    {
      //axis->setLabel(newLabel);
      //ui->customPlot->replot();
        end = Y.toDouble();
    }
    //customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);             // 鼠标框选
    //customPlot->graph()->setSelectable(QCP::stDataRange);
    double length =200/10;
    int xstart = start*length, xend=end*length;
  int n = 200; // number of points in graph
  double xScale = (std::rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (std::rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (std::rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (std::rand()/(double)RAND_MAX - 0.5)*10;
  double r1 = (std::rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (std::rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (std::rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (std::rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  customPlot->addGraph();
  customPlot->graph()->setName(QString("New graph %1").arg(customPlot->graphCount()-1));//设置曲线名称
  customPlot->graph()->setData(x, y);//导入数据
  customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(1));//设置
  customPlot->graph()->setScatterStyle(QCPScatterStyle::ssNone);//设置散点形状
  QPen graphPen;
  graphPen.setColor(QColor(64,64,64));
  graphPen.setWidthF(1);
  customPlot->graph()->setPen(graphPen);

  //customPlot->graph()->setBrush(QBrush(QColor(0,0,255,255)));
  customPlot->replot();
}

void MainWindow::selectionChanged()
{
    std::cout<<customPlot->graphCount()<<"::"<<customPlot->selectedGraphs().size()<<std::endl;
    for (int i=0; i<customPlot->graphCount(); ++i)
    {
      QCPGraph *graph =customPlot->graph(i);
      //QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
      if ( graph->selected())
      {

       //;// graph->setBrush(QBrush(QColor(0,245,255,255)));
          double dataValue = graph->interface1D()->dataMainValue(i);
          double dataXValue = graph->interface1D()->dataMainKey(i);
          QString message = QString("Clicked on graph '%1' at data point #%2  with Xvalue %3 ").arg(graph->name()).arg(i).arg(dataXValue)+QString("Yvlaue: %3.").arg(dataValue);
          textEdit->setText(message);
          int ms= ((int)graph->interface1D());
          std::cout<<i<<"selectionChanged idpoint:"<<graph->interface1D()<<":"<<graph->interface1D()->dataMainKey(i)<<"int:"<<std::hex << static_cast<unsigned int>(ms)<<std::endl;
          std::cout<<message.toStdString()<<std::endl;
      }
    }
}
void MainWindow::removeSelectedGraph()
{

    if (customPlot->selectedGraphs().size() > 0)
    {
        customPlot->removeGraph(customPlot->selectedGraphs().first());
        customPlot->replot();
    }

}
void MainWindow::removeAllGraphs()
{
    customPlot->clearGraphs();
    customPlot->replot();

}
void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    std::cout<<"graphClicked:"<<std::endl;
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    double dataXValue = plottable->interface1D()->dataMainKey(dataIndex);
    QString message = QString("Clicked on graph '%1' at data point #%2  with Xvalue %3 ").arg(plottable->name()).arg(dataIndex).arg(dataXValue)+QString("Yvlaue: %3.").arg(dataValue);
    textEdit->setText(message);
    int ms= ((int)plottable->interface1D());
    std::cout<<dataIndex<<"graphClicked idpoint:"<<plottable->interface1D()<<":"<<plottable->interface1D()->dataMainKey(dataIndex)<<"int:"<<std::hex << static_cast<unsigned int>(ms)<<std::endl;
    std::cout<<message.toStdString()<<std::endl;
}
void  MainWindow::selectToggle (bool checked)
{
    std::cout<<"Toggle: "<<checked<<std::endl;

    if(checked)
    {
        customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
        mGraph->setSelectable(QCP::stDataRange);
        std::cout<<"srmSelect"<<std::endl;
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
        std::cout<<"srmNoSelect"<<std::endl;
    }
}

MainWindow::~MainWindow()
{
}

