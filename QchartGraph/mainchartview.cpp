#include "mainchartview.h"
#include <iostream>
using namespace std;

mainchartview::mainchartview(QChart *chart, QWidget *parent):
        QChartView(chart, parent)
{
    m_chart = chart;
}

void mainchartview::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
       dataStart = m_chart-> mapToValue(event->pos()).x();
       cout<<"data:"<<dataStart<<endl;
       m_mousePress=true;
       emit sendMouseXY(m_chart-> mapToValue(event->pos()).x(),m_chart-> mapToValue(event->pos()).y());
    }
}
void mainchartview::mouseReleaseEvent(QMouseEvent *event)
{


    m_mousePress=false;
    cout<<m_mousePress<<endl;
    if(m_mouseMove==true){
        m_mouseMove=false;
        //cout<<"data:"<<dataStart<<"end:"<<dataEnd<<endl;
        emit sendMouseReleaseEvent(m_mousePress,dataStart,dataEnd);


    //cout<<"data:"<<dataStart<<"end:"<<dataEnd<<endl;
    }
     emit sendMouseXY(m_chart-> mapToValue(event->pos()).x(),m_chart-> mapToValue(event->pos()).y());

}
void mainchartview::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mousePress){
        m_mouseMove=true;
        dataEnd = m_chart-> mapToValue(event->pos()).x();
        emit sendMouseXY(m_chart-> mapToValue(event->pos()).x(),m_chart-> mapToValue(event->pos()).y());
        cout<<"X:"<<m_chart-> mapToValue(event->pos()).x()<<"Y:"<<m_chart-> mapToValue(event->pos()).y()<<endl;

    }
}
