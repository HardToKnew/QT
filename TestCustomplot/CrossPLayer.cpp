#include "CrossPLayer.h"
#include "myqcustomplot.h"

struct CrossPLayerPlotPrivate
{
    //QCP::LineStates m_bIsVisible;
    bool m_bLeftButtonPress = false;
    double m_dAxisXValue = -1;
    QPoint m_MousePoint;
    QCPPainter * m_pPainter = nullptr;
    QPen m_Pen = QPen(Qt::black, 1, Qt::DashDotLine);
    MyQCustomPlot * m_pParentPlot = nullptr;
};

CrossPLayer::CrossPLayer(MyQCustomPlot* parentPlot, const QString &layerName)
            : QCPLayerable(parentPlot,layerName)
            , d_ptr(new CrossPLayerPlotPrivate)
{
    d_ptr->m_pParentPlot=parentPlot;
    mParentPlot->addLayer(LayerName());
    setLayer(LayerName());
}

QString CrossPLayer::LayerName() const
{
    return QStringLiteral("crossline");;
}

/*void CrossPLayer::setVisible(bool visible)
{
    QCPLayer * layer = mParentPlot->layer(LayerName());
    if (layer)
    {
        layer->setVisible(visible);
    }
}*/

/*void CrossPLayer::SetPen(const QPen &pen)
{
    d_ptr->m_Pen = pen;
}*/

void CrossPLayer::draw(QCPPainter *painter)
{
    Q_UNUSED(painter);

    d_ptr->m_pPainter = painter;
    d_ptr->m_pPainter->setPen(d_ptr->m_Pen);

}
