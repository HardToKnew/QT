#include "myqcustomplot.h"
#include <iostream>
using namespace std;
MyQCustomPlot::MyQCustomPlot(QWidget *parent):
    QCustomPlot(parent)
{
    //mParentPlot=new QCustomPlot;



    

    addLayer(QStringLiteral("crossLayer"));
    cusorLayer=this->layer("crossLayer");
    cusorLayer->setVisible(true);
    mLayers.append(cusorLayer);
    cusorLayer->children();
    //cusorLayer->
    mGraph=this->addGraph(this->xAxis,this->yAxis);
    mGraph->setPen(QPen(QColor(5, 5, 5)));
    mGraph->setPen(QPen(Qt::DashLine));//游标线型：虚线
    //timer100ms = new QTimer(this);
    //timer100ms->setInterval(10);
    //connect(timer100ms, SIGNAL(timeout()), this, SLOT(viewTimelyFresh()));
    connect(this,&MyQCustomPlot::MouseEvent,this,&MyQCustomPlot::onCursor);
    //timer100ms->start();
    /*mmGraph=this->addGraph();
    mmGraph->setPen(QPen(QColor(5, 5, 5)));
    mmGraph->setPen(QPen(Qt::DashLine));//游标线型：虚线*/

    //cusorLayer->children(mmGraph);
}

void MyQCustomPlot::paintEvent(QPaintEvent *event)
{
    //调用父类的paintEvent使QCustomPlot可以被重绘
    QCustomPlot::paintEvent(event);
    //在父类重绘完的基础上进行绘制
    //MyQCustomPlot::onCursor(mevent);
    //新建painter
    QPainter painter(this);
    //painter设置Pen
    painter.setPen(QPen(QColor(5, 5, 5)));
    painter.setPen(QPen(Qt::DashLine));
    //QColor color(100,255,100);
   // color.setAlphaF(0.3);
    //painter设置Brush
   // painter.setBrush(QBrush(color));

    painter.drawLine(point_start, point_end);
    cout<<"paintEvent is ok!"<<point_start.x()<<endl;
}

void MyQCustomPlot::mousePressEvent(QMouseEvent *event)
{
    double x_pos=event->pos().x();
    QCustomPlot::mousePressEvent(event);
    if(this->viewport().contains(event->pos()))
    {
        if(event->button() == Qt::LeftButton&&
                event->pos().x()>=this->xAxis->coordToPixel(this->xAxis->range().lower)
                &&event->pos().x()<=this->xAxis->coordToPixel(this->xAxis->range().upper))
        {
            isLeftMousePress = true;
            MousePress = true;

            point_start.setX(event->pos().x());
            point_start.setY(this->yAxis->range().lower);
            point_end.setX(event->pos().x());
            point_end.setY(this->yAxis->range().upper);
            point_start.setX(event->pos().x());
            point_start.setY(this->yAxis->coordToPixel(this->yAxis->range().lower));
            point_end.setX(event->pos().x());
            point_end.setY(this->yAxis->coordToPixel(this->yAxis->range().maxRange));
            emit MouseEvent(event);
            update();
            //xMousePix=event->pos().x();
            //xMousePix=this->xAxis->pixelToCoord(event->pos().x());
        }
    }

}

void MyQCustomPlot::mouseReleaseEvent(QMouseEvent *event)
{
    isLeftMousePress = false;
    QCustomPlot::mouseReleaseEvent(event);
    MousePress = false;
}
void MyQCustomPlot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);
    double x_pos=event->pos().x();//16 yAxis pixe  790 pixe 16384  缩放有影响
    if(this->viewport().contains(event->pos())&&
            event->pos().x()>=this->xAxis->coordToPixel(this->xAxis->range().lower)
            &&event->pos().x()<=this->xAxis->coordToPixel(this->xAxis->range().upper))
    {
        if(isLeftMousePress ==true)
        {
            //this->clearGraphs();
            MousePress = false;
            this->xAxis->pixelToCoord(event->pos().x());
            this->yAxis->pixelToCoord(event->pos().y());

            //cout<<"mPointX:"<<mPointX<<endl;
            QVector<double> xValues,yValues;
            //emit MouseEvent(event);
            point_start.setX(event->pos().x());
            point_start.setY(this->yAxis->coordToPixel(this->yAxis->range().lower));
            point_end.setX(event->pos().x());
            point_end.setY(this->yAxis->coordToPixel(this->yAxis->range().maxRange));
            update();
            emit MouseEvent(event);

            /*xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(0);
            xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(this->yAxis->range().size()/2);
            xValues.append(this->xAxis->pixelToCoord(event->pos().x()));
            yValues.append(this->yAxis->range().size());
            this->addGraph();
            this->graph()->setData(xValues,yValues);
            this->graph()->setPen(QPen(QColor(5, 5, 5)));
            this->graph()->setPen(QPen(Qt::DashLine));//游标线型：虚线
            this ->replot(QCustomPlot::rpQueuedReplot);*/
        }
    }
        //cout<<this->viewport().contains(event->pos())<<endl;
        //cout<<(event->button() == Qt::LeftButton)<<"x:"<<x_pos<<"   "<<this->xAxis->pixelToCoord(x_pos)<<"  "<< ""<<endl;

}
void MyQCustomPlot::onCurso(QMouseEvent *event)
{
    mevent=event;
}
void MyQCustomPlot::onCursor(QMouseEvent *event)
{
    /*QVector<double> xValues,yValues;

    double xValue = this->xAxis->pixelToCoord(event->pos().x());
    xValues.append(xValue);
    yValues.append(0);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size()/2);
    xValues.append(xValue);
    yValues.append(this->yAxis->range().size());
    mGraph->setData(xValues,yValues);
    this ->replot(QCustomPlot::rpQueuedReplot);*/
    /*QPainter painter(this);
    //painter设置Pen
    painter.setPen(QPen(QColor(200,255,222)));
    QColor color(100,255,100);
    color.setAlphaF(0.3);
    //painter设置Brush
    painter.setBrush(QBrush(color));

    painter.drawLine(point_start, point_end);*/
}
/*void MyQCustomPlot::viewTimelyFresh()
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
