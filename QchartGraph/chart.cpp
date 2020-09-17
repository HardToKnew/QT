#include "chart.h"


Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags, QLineSeries *series)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags), m_series(series)
{

}

Chart::~Chart()
{
}
