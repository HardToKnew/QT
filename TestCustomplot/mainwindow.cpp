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

    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);//开启QWidget::customContextMenuRequested信号
    connect(customPlot, &QWidget::customContextMenuRequested, this, &MainWindow::contextMenuRequest);

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

    QAction *printQAc = new QAction(tr("打印"),toolBar);
    toolBar->addAction(printQAc);
    connect(printQAc,&QAction::triggered,this,&MainWindow::printAction);



}
void MainWindow::setupDemo(QCustomPlot *customPlot)
{
    mGraph=customPlot->addGraph();//setSelectionRectMode(QCP::srmSelect);
    customPlot->graph();
    QColor color(0,0, 255);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color.lighter(200)));

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
            r.remove(QRegExp("\\s"));
            if(r.contains(str,Qt::CaseSensitive)){
                tableDialog->tableWidget->removeEntry(i);

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
void MainWindow::printAction()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
       //自定义纸张大小，特别重要，不然预览效果极差
       printer.setPageSize(QPrinter::Custom);
       printer.setPaperSize(QSizeF(600, 800),
                                  QPrinter::Point);
       QPrintPreviewDialog preview(&printer, this);// 创建打印预览对话框

       preview.setMinimumSize(1000,600);
       /*
        * QPrintPreviewDialog类提供了一个打印预览对话框，里面功能比较全，
        * paintRequested(QPrinter *printer)是系统提供的，
        * 当preview.exec()执行时该信号被触发，
        * drawPic(QPrinter *printer)是自定义的槽函数，图像的绘制就在这个函数里。
        */
       //connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(drawPic(QPrinter*)));
       connect(&preview, &QPrintPreviewDialog::paintRequested, this,&MainWindow::drawPic);
       preview.exec();
}

void MainWindow::drawPic(QPrinter *printerPixmap)
{
    QPixmap pix = QPixmap(800,600);
    //这个函数算是画模板的函数吧，毕竟打印时有模板的
    createPix(&pix);
    //pix.save(sFilePix);
    //纵向：Portrait 横向：Landscape
    //printerPixmap->setOrientation(QPrinter::Landscape);
    //获取界面的图片
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / pix.width();
    int y = rect.height() / pix.height();
    //设置图像长宽是原图的多少倍
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, pix);
    painterPixmap.end();
}
void MainWindow::createPix(QPixmap *pix)
{
    QPainter *painter = new QPainter(this);
       painter->begin(pix);
       painter->setRenderHint(QPainter::Antialiasing, true);
       // 设置画笔颜色、宽度
       painter->setPen(QPen(QColor(255, 255, 255), 2));
       // 设置画刷颜色
       painter->setBrush(QColor(255, 255, 255));
       QRect rect(0,0,800,600);
       //整张图设置画刷白底
       painter->fillRect(rect,QColor(255, 255, 255));
       painter->drawRect(rect);
       //画数据部分的线条
       painter->setPen(QPen(QColor(0, 0, 0)));
       QVector<QLine> lines;
       lines.append(QLine(QPoint(50,50),QPoint(750,50)));//上边
       lines.append(QLine(QPoint(55,45),QPoint(55,550)));//1
       lines.append(QLine(QPoint(155,45),QPoint(155,550)));//1
       painter->drawLines(lines);
    QFont font;
    font.setPointSize(13);
    font.setFamily("黑体");
    font.setItalic(true);
    painter->setFont(font);

    painter->end();
}

/*bool MainWindow::newPage()
{
    MainWindow::printAction();
}*/


MainWindow::~MainWindow()
{
}

