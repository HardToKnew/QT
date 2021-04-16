#include "model_roidetails.h"

Model_ROIDetails::Model_ROIDetails(QMainWindow *parent)
                   :QMainWindow(parent)
                   , ui(new Ui::MainWindow)
{

}

void Model_ROIDetails::setupUI(QMainWindow *parent)
{
    ui->setupUi(parent);
}
