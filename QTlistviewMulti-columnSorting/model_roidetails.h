#ifndef MODEL_ROIDETAILS_H
#define MODEL_ROIDETAILS_H

#include <QObject>
#include <QMainWindow>

#include "ui_roidetails.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Model_ROIDetails:public QMainWindow
{
    Q_OBJECT
public:
    Model_ROIDetails(QMainWindow *parent=nullptr);
    void setupUI(QMainWindow *parent=nullptr);
private:
    Ui::MainWindow *ui;
};
namespace ui {
        class MainWindow: public Model_ROIDetails {};
    }


#endif // MODEL_ROIDETAILS_H
