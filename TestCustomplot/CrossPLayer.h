#ifndef CROSSPLAYER_H
#define CROSSPLAYER_H
#include <QtCore/QString>

#include "qcustomplot.h"

class MyQCustomPlot;
struct CrossPLayerPlotPrivate;

class CrossPLayer : public  QCPLayerable
{
    /*enum LayerMode {//分层绘制原理
              lmLogical   ///< Layer is used only for rendering order, and shares paint buffer with all other adjacent logical layers.
              , lmBuffered ///< Layer has its own paint buffer and may be replotted individually (see \ref replot).
          };*/
    Q_OBJECT
signals :
    void DrawCrossLine(const QPoint & pos);
public:
    CrossPLayer(MyQCustomPlot* parentPlot, const QString &layerName);
    // setters:
    QString LayerName() const;
    //void setVisible(bool visible);//设置层是否可见
    //void SetPen(const QPen & pen);//设置十字线画笔

    // non-virtual methods:
    void replot();//重新绘制层
protected:
     QCustomPlot *mParentPlot;//所在图表
     QString mName;//层名称
     int mIndex;//层序，决定绘制先后顺序
     QList<QCPLayerable*> mChildren;//层中所有元素
     bool mVisible;//是否可见标记
 //    LayerMode mMode;//绘制模式标记

     // non-property members:
     QWeakPointer<QCPAbstractPaintBuffer> mPaintBuffer;//绘制缓冲区
     // non-virtual methods:
    void draw(QCPPainter *painter);//使用painter绘制
     void drawToPaintBuffer();//绘制到缓冲区
     void addChild(QCPLayerable *layerable, bool prepend);//新增元素
     void removeChild(QCPLayerable *layerable);//移除元素
private:
     QScopedPointer<CrossPLayerPlotPrivate> d_ptr;
};

#endif // CROSSPLAYER_H
