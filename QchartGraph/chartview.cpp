#include "chartview.h"
#include <QBoxLayout>
#include <QAreaSeries>
#include <iostream>
#include <QtWidgets>
#include <QPainter>

using namespace std;
bool m_mousePress;
int dataStart,dataEnd;
int number[1000];
chartview::chartview(QWidget *parent)
          :QWidget(parent)//QChartView(parent)//QWidget(parent)
{

    QBoxLayout *HHHH=new QHBoxLayout;
    //QChartView *chartView;
    //QChart *
    chart = new QChart();
    chart->setTitle("Simple areachart example");
    chartView = new mainchartview(chart);



    QLineSeries *upperSeries = new QLineSeries();
    QLineSeries *lowerSeries= new QLineSeries();
    for (int i=0; i < 50; i++) {
        number[i]=i;
      }
    for (int i=50; i < 100; i++) {
        number[i]=0;
      }
    for (int i=0; i < 100; i++) {

          upperSeries->append(QPointF(i, powf((float)number[i],0.5)));

          lowerSeries->append(QPointF(i, 0));

      }



    area = new QAreaSeries(upperSeries, lowerSeries);

    chart->addSeries(area);
    chart->createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);

        QLineSeries *upperSeries1 = new QLineSeries();
        QLineSeries *lowerSeries1= new QLineSeries();
        for (int i=50; i < 52; i++) {

              //number[i]=i;
              upperSeries1->append(QPointF(i,powf((float)number[i],0.5)));

              lowerSeries1->append(QPointF(i, 0));

          }
        QAreaSeries *area1 = new QAreaSeries(upperSeries1, lowerSeries1);

        chart->addSeries(area1);
        chart->createDefaultAxes();
        chartView->setRenderHint(QPainter::Antialiasing);

        axisXSeries = new QLineSeries;
        axisYSeries = new QLineSeries;
        axisYSeries->setColor(QColor(255,1,1,255));
        axisXSeries->setColor(QColor(255,1,1,255));
        chart->addSeries(axisXSeries);
        chart->addSeries(axisYSeries);
        chart->createDefaultAxes();
        chartView->setRenderHint(QPainter::Antialiasing);




    HHHH->addWidget(chartView);
    this->setLayout(HHHH);

    connect(chartView,&mainchartview::sendMouseReleaseEvent,this,&chartview::updataChartview);
    connect(chartView,&mainchartview::sendMouseXY,this,&chartview::CrossLine);


}

chartview::~chartview()
{

}
void chartview::updataChartview(bool mousePress,int start, int end)
{
    if(start>end)
    {
        int number;
        number = start;
        start = end;
        end = number;

    }
    dataStart=start;
    dataEnd = end;
    cout<<"ok"<<endl;
    if(mousePress==false){
        cout<<"data1:"<<dataStart<<"end:"<<dataEnd<<endl;
        QLineSeries *upperSeries2 = new QLineSeries();
        QLineSeries *lowerSeries2= new QLineSeries();
        for (int i=dataStart; i < dataEnd; i++) {

          //number[i]=i;
            upperSeries2->append(QPointF(i, powf((float)number[i],0.5)));

            lowerSeries2->append(QPointF(i, 0));

        }
        QAreaSeries *area2 = new QAreaSeries(upperSeries2, lowerSeries2);

        chart->addSeries(area2);
        chart->createDefaultAxes();
        chartView->setRenderHint(QPainter::Antialiasing);
        /*delete axisXSeries;
        delete axisYSeries;
        axisXSeries = new QLineSeries;
        axisYSeries = new QLineSeries;*/
    }
}
void chartview::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));//设置画笔形式
    painter.drawLine(20,20,220,220);//画直线
    painter.drawLine(20,220,220,20);
    painter.drawEllipse(20,20,200,200);//画圆
    painter.drawRect(20,20,200,200);//画矩形
}
void chartview::CrossLine(float x, float y)
{
    delete axisXSeries;
    delete axisYSeries;
    QVector<QPointF> axisX;
    QVector<QPointF> axisY;
    for(int i=0;i<100; i++)
    {
        axisX.append(QPointF(i,y));

    }
    for(int i=0;i<1000; i++)
    {
        axisY.append(QPointF(x,i));

    }
    axisXSeries = new QLineSeries;
    axisYSeries = new QLineSeries;
    axisYSeries->setColor(QColor(255,1,1,255));
    axisXSeries->setColor(QColor(255,1,1,255));
    chart->addSeries(axisXSeries);
    chart->addSeries(axisYSeries);
    chart->createDefaultAxes();
    chartView->setRenderHint(QPainter::Antialiasing);
    axisXSeries->replace(axisX);
    axisYSeries->replace(axisY);

}
