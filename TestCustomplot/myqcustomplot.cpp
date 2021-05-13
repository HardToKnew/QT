#include "myqcustomplot.h"
#include <iostream>
using namespace std;
MyQCustomPlot::MyQCustomPlot(QWidget *parent):
    QCustomPlot(parent)
{
    //mParentPlot=new QCustomPlot;

    //mGraph=this->addGraph(this->xAxis,this->yAxis);
    //mGraph->setPen(QPen(QColor(5, 5, 5)));
    //mGraph->setPen(QPen(Qt::DashLine));//游标线型：虚线
    //timer100ms = new QTimer(this);
    //timer100ms->setInterval(10);
    //connect(timer100ms, SIGNAL(timeout()), this, SLOT(viewTimelyFresh()));
   // connect(this,&MyQCustomPlot::MouseEvent,this,&MyQCustomPlot::onCursor);
    //timer100ms->start();
    mmGraph=this->addGraph();
    mmGraph->setPen(QPen(QColor(5, 5, 5)));
    mmGraph->setPen(QPen(Qt::DashLine));//游标线型：虚线
}

void MyQCustomPlot::mousePressEvent(QMouseEvent *event)
{
    double x_pos=event->pos().x();
    QCustomPlot::mousePressEvent(event);
    if(this->viewport().contains(event->pos()))
    {
        if(event->button() == Qt::LeftButton)
        {
            isLeftMousePress = true;
            //MousePress = true;
            //emit MouseEvent(event);
            //xMousePix=event->pos().x();
            //xMousePix=this->xAxis->pixelToCoord(event->pos().x());
        }
    }

}

void MyQCustomPlot::mouseReleaseEvent(QMouseEvent *event)
{
    isLeftMousePress = false;
    QCustomPlot::mouseReleaseEvent(event);
    //MousePress = false;
}
void MyQCustomPlot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);
    double x_pos=event->pos().x();//16 yAxis pixe  790 pixe 16384  缩放有影响
    if(this->viewport().contains(event->pos()))//在区域范围
    {
        if(isLeftMousePress ==true)
        {
            //this->clearGraphs();
            /*MousePress = false;
            this->xAxis->pixelToCoord(event->pos().x());
            this->yAxis->pixelToCoord(event->pos().y());

            //cout<<"mPointX:"<<mPointX<<endl;
            QVector<double> xValues,yValues;


            xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(0);
            xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(this->yAxis->range().size()/2);
            xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(this->yAxis->range().size());
            this->addGraph();
            this->graph()->setData(xValues,yValues);
            this->graph()->setPen(QPen(QColor(5, 5, 5)));
            this->graph()->setPen(QPen(Qt::DashLine));//游标线型：虚线*/
            this ->replot(QCustomPlot::rpQueuedReplot);
        }
    }
        //cout<<this->viewport().contains(event->pos())<<endl;
        //cout<<(event->button() == Qt::LeftButton)<<"x:"<<x_pos<<"   "<<this->xAxis->pixelToCoord(x_pos)<<"  "<< ""<<endl;

}
/*void MyQCustomPlot::onCursor(QMouseEvent *event)
{
    QVector<double> xValues,yValues;

    double xValue = this->xAxis->pixelToCoord(event->pos().x());
    xValues.append(xValue);
    yValues.append(0);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size()/2);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size());
    mGraph->setData(xValues,yValues);
    this ->replot(QCustomPlot::rpQueuedReplot);
}
void MyQCustomPlot::viewTimelyFresh()
{
    QVector<double> xValues,yValues;

    double xValue = xMousePix;
    xValues.append(xValue);
    yValues.append(0);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size()/2);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size());
    mGraph->setData(xValues,yValues);
    this ->replot(QCustomPlot::rpQueuedReplot);
}*/
