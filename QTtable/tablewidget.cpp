#include "tablewidget.h"
#include "adddialog.h"
#include <QHeaderView>
#include <QPushButton>

TableWidget::TableWidget(QMainWindow *parent)
    : QTabWidget(parent)
{
    table = new TableModel();
    this->setupTab(parent);
    //parent->setLayout()

    //this->setCurrentWidget(this);

}

void TableWidget::setupTab(QMainWindow *mainwindow)
{


    widget=new QTabWidget(mainwindow) ;
    mainlayout = new QHBoxLayout(widget);

    QTableView *tableView = new QTableView(widget);
    tableView->setModel(table);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    const int Width=80;
    tableView->setColumnWidth(0, Width);
    tableView->setColumnWidth(1, Width);
    tableView->setColumnWidth(2, Width);
    tableView->setColumnWidth(3, Width);
    tableView->setColumnWidth(4, Width);
    tableView->setColumnWidth(5, Width);
    tableView->setColumnWidth(6, Width);
    mainlayout->addWidget(tableView);
    mainwindow->setCentralWidget(widget);
//

}

void TableWidget::showAddEntryDialog()
{
    adddialog aDialog;

    if (aDialog.exec()) {
        QString start = aDialog.startText->text();
        QString end = aDialog.endText->text();
        QString FWHM = aDialog.fhwmText->text();
        QString netArea = aDialog.netAreaText->text();
        QString grossArea = aDialog.grossAreaText->text();
        QString centroid = aDialog.centroidText->text();
        QString uncertainty = aDialog.uncertaintyText->text();


        addEntry(start, end, FWHM, netArea, grossArea,centroid,uncertainty);
    }

}

void TableWidget::addEntry(QString start, QString end, QString fhwm, QString netArea, QString grossArea, QString centroid, QString uncertainty)
{
    QList<ModelItem>  list = table->getList();
    //QList<QString, QString>
    //ModelItem pair{start.toDouble(),end.toDouble(),fhwm.toDouble(),netArea.toInt(),grossArea.toInt(),centroid.toDouble(),uncertainty.toDouble()};

        //if (!list.contains(pair)) {
            table->insertRows(0, 1, QModelIndex());

            QModelIndex index = table->index(0, 0, QModelIndex());
            table->setData(index, start.toDouble(), Qt::EditRole);
            index = table->index(0, 1, QModelIndex());
            table->setData(index, end.toDouble(), Qt::EditRole);
            index = table->index(0, 2, QModelIndex());
            table->setData(index, fhwm.toDouble(), Qt::EditRole);
            index = table->index(0, 3, QModelIndex());
            table->setData(index, netArea.toInt(), Qt::EditRole);
            index = table->index(0, 4, QModelIndex());
            table->setData(index, grossArea.toInt(), Qt::EditRole);
            index = table->index(0, 5, QModelIndex());
            table->setData(index, centroid.toDouble(), Qt::EditRole);
            index = table->index(0, 6, QModelIndex());
            table->setData(index, uncertainty.toDouble(), Qt::EditRole);
            //removeTab(indexOf(newAddressTab));
        /*} else {
            QMessageBox::information(this, tr("Duplicate Name"),
                tr("The start \"%1\" already exists.").arg(start));
        }*/


}
