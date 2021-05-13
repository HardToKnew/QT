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
    QPointer<QCPGraph> mmGraph;//光标
private:



   // QTimer *timer100ms = nullptr;
    //double xMousePix=0;

private slots:
    //void viewTimelyFresh();
public slots:
    //void onCursor(QMouseEvent *event);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
};

#endif // MYQCUSTOMPLOT_H
