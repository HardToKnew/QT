#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "tabledialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QCustomPlot *customPlot;
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QListWidget *listWd;
    QPointer<QCPGraph> mGraph;

    TableDialog *tableDialog;
    QAction *selectQAc;

    bool select=false;
    //QFrame *frame;
    //QFrame *frame2;

    void setToolBar(QMainWindow *mainWindow);
    void setupDemo(QCustomPlot *customPlot);

private slots:
    void contextMenuRequest(QPoint);
    void addRandomGraph();
    void selectionChanged();
    void removeSelectedGraph();
    void removeAllGraphs();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void selectToggle (bool checked);
    void tableAction ();
};
#endif // MAINWINDOW_H
