#include "tablewidget.h"
#include <QHeaderView>
#include <QPushButton>

TableWidget::TableWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel();
    this->setupTab();

    //this->setCurrentWidget(this);

}

void TableWidget::setupTab()
{


    //widget=new QTabWidget() ;

    //QPushButton *ll=new QPushButton();
    //ll->setText("ok");
    //centralwidget = new QTabWidget(this);

    //mainlayout = new QHBoxLayout();
    //widget

    QTableView *tableView = new QTableView(this);
    tableView->setModel(table);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //tableView.*/

   // mainlayout->addWidget(widget);
    //this->setCornerWidget(widget);;
    //this->setLayout(mainlayout);
    //MAINLayout->addWidget(widget);
    //setCentralWidget(centralwidget);
//

}
