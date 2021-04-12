#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dowork();

private:
    Ui::MainWindow *ui;
    Worker *m_pworker;
    QThread *m_pthread;
signals:
    void sig_dowork();
public slots:
    void slot_finish();
private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
