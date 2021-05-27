#ifndef MYQCUSTOMPLOT_H
#define MYQCUSTOMPLOT_H

#include <QObject>
#include <qcustomplot.h>
class MyQCustomPlot:public QCustomPlot
{
    Q_OBJECT
public:
    MyQCustomPlot(QWidget *parent=0);
    bool isLeftMousePress = false;
    bool MousePress =false;
    QPointer<QCPGraph> mGraph,mmGraph;//光标
    QCPLayer *cusorLayer;
private:
    QMouseEvent *mevent;
    QPointF point_start;
    QPointF point_end;

   // QTimer *timer100ms = nullptr;
    //double xMousePix=0;

private slots:
    //void viewTimelyFresh();
public slots:
    void onCurso(QMouseEvent *event);
    void onCursor(QMouseEvent *event);
protected:

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void MouseEvent(QMouseEvent *event);
    //void sMouseEvent(QMouseEvent *event);
};


#endif // MYQCUSTOMPLOT_H
