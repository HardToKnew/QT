#ifndef MAINCHARTVIEW_H
#define MAINCHARTVIEW_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

class Chart;

QT_CHARTS_USE_NAMESPACE

class mainchartview:public QChartView
{
    Q_OBJECT
public:
    mainchartview(QChart *chart, QWidget *parent = 0);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QChart *m_chart;
    bool m_mousePress,m_mouseMove;
    int dataStart,dataEnd;
signals:
    void sendMouseReleaseEvent(bool m_mousePress, int datastart,int dataend);
    void sendMouseXY(float x,float y);
};

#endif // MAINCHARTVIEW_H
