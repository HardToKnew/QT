#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QAreaSeries>
#include <QMouseEvent>
#include "mainchartview.h"

QT_CHARTS_USE_NAMESPACE

class chartview: public  QWidget//QChartView//QWidget

{
    Q_OBJECT
public:
    chartview(QWidget *parent=nullptr);
    ~chartview();
protected:
    /*void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);*/
    void paintEvent(QPaintEvent *);
private:
    QChart *chart;
    QAreaSeries *area;
    mainchartview *chartView;
    QLineSeries *axisXSeries,*axisYSeries;
    void updataChartview(bool mosePress,int datastart,int dataend);
    void CrossLine(float x,float y);
signals:
    void sendMouseReleaseEvent(bool m_mousePress);
};

#endif // CHARTVIEW_H
