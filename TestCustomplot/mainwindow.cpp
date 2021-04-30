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

    tableDialog = new TableDialog(this);



    customPlot = new QCustomPlot(centralWidget);
    customPlot->xAxis->setRange(-10, 10);
    customPlot->yAxis->setRange(0, 15);
    customPlot->setInteractions(/*QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes |
                                      QCP::iSelectLegend |*/ QCP::iSelectPlottables);// 设置相应的枚举量选中图表
    //customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);


    textEdit = new QTextEdit(centralWidget);
    listWd = new QListWidget(centralWidget);

    QBoxLayout *herticalLayout=new QHBoxLayout(centralWidget);
    centralWidget->setLayout(herticalLayout);

    QBoxLayout *verticalLayout=new QVBoxLayout();
    verticalLayout->addWidget(customPlot,4);
    verticalLayout->addWidget(textEdit,1);


    herticalLayout->addLayout(verticalLayout,7);
    herticalLayout->addWidget(listWd,3);


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

    QAction *tableQAc = new QAction(tr("表格"),toolBar);
    toolBar->addAction(tableQAc);
    connect(tableQAc,&QAction::triggered,this,&MainWindow::tableAction );


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
    customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    mGraph->setSelectable(QCP::stNone);
  //}
  // show legend with slightly transparent background brush:
  //customPlot->legend->setVisible(true);
  //customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}
void MainWindow::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction("Add random graph", this, &MainWindow::addRandomGraph);
    if (customPlot->selectedGraphs().size() > 0)
        menu->addAction("Remove selected graph", this, &MainWindow::removeSelectedGraph);
    if (customPlot->graphCount() > 0)
        menu->addAction("Remove all graphs", this, &MainWindow::removeAllGraphs);
    menu->popup(customPlot->mapToGlobal(pos));
}
void MainWindow::addRandomGraph()
{
    bool ok;
    double start=0,end=10;
    QString X = QInputDialog::getText(this, "QCustomPlot example", "x:", QLineEdit::Normal, "0", &ok);
    if (ok)
        start=X.toDouble();
    QString Y = QInputDialog::getText(this, "QCustomPlot example", "y:", QLineEdit::Normal, "10", &ok);
    if (ok)
        end = Y.toDouble();
    int Bengin,End;
    Bengin = mGraph->data()->findBegin(start)-mGraph->data()->constBegin();
    End = mGraph->data()->findBegin(end)-mGraph->data()->constBegin();
    QString Strstart = QString::number(mGraph->data()->at(Bengin)->key);
    QString Strend = QString::number(mGraph->data()->at(End)->key);
    tableDialog->tableWidget->addEntry(Strstart,Strend,"0","0","0","0","0");

    int n = End-Bengin; // number of points in graph
    QVector<double> x(n), y(n);
    for(int i=0,k=Bengin;k<End;i++,k++)
    {
        QString str_key = QString::number(mGraph->data()->at(k)->key);
        QString str_value = QString::number(mGraph->data()->at(k)->value);
        x[i]=mGraph->data()->at(k)->key;
        y[i]=mGraph->data()->at(k)->value;
        QString message =str_key+"::"+str_value;
        listWd->addItem(message);
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

    customPlot->graph()->setBrush(QBrush(QColor(0,0,255,255)));
    customPlot->replot();
}

void MainWindow::selectionChanged()
{
    listWd->clear();
    QString message;
    if(mGraph->selected()&&select)
    {
        QCPDataSelection selection =mGraph->selection();
        QCPDataRange dataRange = selection.dataRange();//选中一个区域
        int n= dataRange.end()-dataRange.begin();
        QVector<double> x(n), y(n);
        for(int i=0,k=dataRange.begin();k<dataRange.end();i++,k++)
        {
            QString str_key = QString::number(mGraph->data()->at(k)->key);
            QString str_value = QString::number(mGraph->data()->at(k)->value);
            x[i]=mGraph->data()->at(k)->key;
            y[i]=mGraph->data()->at(k)->value;
            message ="key:"+str_key+" value:"+str_value;
            listWd->addItem(message);
        }
        QString start = QString::number(mGraph->data()->at(dataRange.begin())->key);
        QString end = QString::number(mGraph->data()->at(dataRange.end())->key);
        tableDialog->tableWidget->addEntry(start,end,"0","0","0","0","0");
        customPlot->addGraph();
        customPlot->graph()->setName(QString("New graph %1").arg(customPlot->graphCount()-1));
        customPlot->graph()->setData(x, y);
        customPlot->graph()->setBrush(QBrush(QColor(0,0,255,255)));
        QPen graphPen;
        graphPen.setColor(QColor(64,64,64));
        customPlot->graph()->setPen(graphPen);
        customPlot->replot();
        textEdit->setText("Beagin:"+QString::number(dataRange.begin()));
    }
}
void MainWindow::removeSelectedGraph()
{
    if (customPlot->selectedGraphs().size() > 0&&customPlot->selectedGraphs().first()!=mGraph)
    {
        QCPGraph *graph=customPlot->selectedGraphs().first();
        QString str=QString::number(graph->data()->constBegin()->key);
        str.remove(QRegExp("\\s"));
        std::cout<<"str:"+str.toStdString()<<std::endl;
        QTableView *tableview=tableDialog->tableWidget->tableView;
        for(int i=0;i<tableview->model()->rowCount();i++)
        {
            //tableview->setRowHidden(i,true);
            QString r="";
            //提取表格第一列数据
            QAbstractItemModel *model=tableview->model();
            QModelIndex index;
            index=model->index(i,0);
            r=model->data(index).toString();
            std::cout<<"r:"+r.toStdString()<<std::endl;
            r.remove(QRegExp("\\s"));
            if(r.contains(str,Qt::CaseSensitive)){
                //tableview->setRowHidden(i,false);//隐藏
                tableDialog->tableWidget->removeEntry(i);
                std::cout<<"delete:"<<r.toStdString()<<std::endl;
            }


        }
        customPlot->removeGraph(customPlot->selectedGraphs().first());
        customPlot->replot();

    }

}
void MainWindow::removeAllGraphs()
{
    for (int i=customPlot->graphCount()-1; i!=0; --i)
    {
      QCPGraph *graph = customPlot->graph(i);
      if(graph!=mGraph)
        customPlot->removeGraph(graph);
    }
    customPlot->replot();

}
void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    textEdit->setText(message);
}
void  MainWindow::selectToggle (bool checked)
{
    select=checked;
    if(checked)
    {
        customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
        mGraph->setSelectable(QCP::stDataRange);
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
        mGraph->setSelectable(QCP::stNone);
    }
}
void MainWindow::tableAction ()
{
    tableDialog->exec();
}

MainWindow::~MainWindow()
{
}

