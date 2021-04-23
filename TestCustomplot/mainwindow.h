#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QCustomPlot *customPlot;
    QWidget *centralWidget;
    //QFrame *frame;
    //QFrame *frame2;

private slots:
    void contextMenuRequest(QPoint);
};
#endif // MAINWINDOW_H
