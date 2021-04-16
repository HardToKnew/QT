#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QTableView>
#include <QtWidgets/QHBoxLayout>
#include <QItemSelection>
#include <QTabWidget>


#include "tablemodel.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE
class TableWidget:public QTabWidget
{
    Q_OBJECT
public:
    TableWidget(QWidget *parent = 0);

    void setupTab();
private:
    TableModel* table;
    QBoxLayout *mainlayout;
    QTabWidget *widget;
    QTabWidget *centralwidget;
};

#endif // TABLEWIDGET_H
