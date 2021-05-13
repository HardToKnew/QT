#ifndef CURSORLAYER_H
#define CURSORLAYER_H
#include <QObject>
#include <myqcustomplot.h>
struct CrossLinePlotPrivate
  {
      QCP::LineStates m_bIsVisible;
      bool m_bLeftButtonPress = false;
      double m_dAxisXValue = -1;
      QPoint m_MousePoint;
      QCPPainter * m_pPainter = nullptr;
      QPen m_Pen = QPen(Qt::black, 1, Qt::DashDotLine);
      MyQCustomPlot * m_pParentPlot = nullptr;
  };
class CursorLayer : public  QCPLayerable
{
     Q_OBJECT
signals :
     void DrawCrossLine(const QPoint & pos);
public:
    CursorLayer(MyQCustomPlot * basePlot, QCustomPlot * plot);
     ~CursorLayer();
public:
     QString LayerName() const;//层名称
     void SetVisible(bool visible);//设置层是否绘制

     void SetPen(const QPen & pen);//设置十字线画笔

     bool MouseButtonDown() const ;
     //bool GetLineVisible(QCP::LineState line) const;
     void SetLineShow(QCP::LineState lines);//设置线是否显示

     //十字线同步注册接口
     bool RegisiterBortherLine(CursorLayer * line);
     bool UnregisiterBortherLine(CursorLayer * line);

 protected:
     virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const{};
     virtual void draw(QCPPainter * painter);

 private:
     void DrawLine(QCPAxis * axis, Qt::Orientation orientation);//画指定方向的坐标轴十字线(严格来说应该是一部分，一条线)
     void SyncLinePosition(const QPoint & pos, double x);//同步线位置

 private slots:
     void MouseMoveHandle(QMouseEvent * event);

 private:
     QScopedPointer<CrossLinePlotPrivate> d_ptr;
     static std::vector<CursorLayer *> m_BrotherLine;//同步其他十字线
};

#endif // CURSORLAYER_H
