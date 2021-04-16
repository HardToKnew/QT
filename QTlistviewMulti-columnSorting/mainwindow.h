#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model_roidetails.h"
QT_BEGIN_NAMESPACE
namespace ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    ui::MainWindow *Ui;
};
#endif // MAINWINDOW_H
