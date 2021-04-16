#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "tablewidget.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    TableWidget* addressWidget;
private:
    void setMenus();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
