#include "ui_roidetails.h"
#include <QSortFilterProxyModel>
#include <QTableView>
Ui_ROIDetails::Ui_ROIDetails(QWidget *parent)
    : QTabWidget(parent)
{

}
void Ui_ROIDetails::setupUi(QMainWindow *MainWindow)
{
  MainWindow->setWindowTitle("1111");

  centralwidget = new QWidget(this);
  centralwidget->setObjectName(QStringLiteral("centralwidget"));

  MainWindow->setCentralWidget(centralwidget);

  widget = new QWidget();
  //widget = new QWidget(MainWindow);
  widget->setObjectName(QStringLiteral("widget"));
  widget->setGeometry(QRect(10, 10, 580, 380));
  //MainWindow->setCentralWidget(widget);

  verticalLayout_2 = new QVBoxLayout(widget);
  verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
  verticalLayout_2->setContentsMargins(0, 0, 0, 0);
  //list =new QListView(widget);
  //verticalLayout_2->addWidget(list);
  //verticalLayout_2->setStretchFactor(list , 1);//设置布局中控件占用空间的比例，所以不用设置控件大小


  MAINLayout =new QHBoxLayout();
  MAINLayout->addWidget(widget);


  centralwidget->setLayout(MAINLayout);
   MAINLayout->addWidget(widget);
  MainWindow->setCentralWidget(centralwidget);


}

void Ui_ROIDetails::setupTabs()
{

}
