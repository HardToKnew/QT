#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QTableView>
#include <QtWidgets/QHBoxLayout>
#include <QItemSelection>
#include <QTabWidget>
#include <QtWidgets>


#include "tablemodel.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE
class TableWidget:public QTabWidget
{
    Q_OBJECT
public:
    TableWidget(QMainWindow *parent = 0);

    void setupTab(QMainWindow *mainwindow=nullptr);
public slots:
    void showAddEntryDialog();
    void addEntry(QString start, QString end, QString fhwm, QString netArea, QString grossArea, QString centroid, QString uncertainty);
private:
    TableModel* table;
    QBoxLayout *mainlayout;
    QTabWidget *widget;
    QTabWidget *centralwidget;
};

#endif // TABLEWIDGET_H
