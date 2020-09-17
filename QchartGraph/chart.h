#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE
class Chart:public QChart
{
    Q_OBJECT
public:
    explicit Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0, QLineSeries *series = 0);
    ~Chart();
    QLineSeries *m_series;
};

#endif // CHART_H
