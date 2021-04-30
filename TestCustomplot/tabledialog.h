#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H
#include <QDialog>
#include "tablewidget.h"


class TableDialog:public QDialog
{
    Q_OBJECT
public:
    TableDialog(QWidget *parent = 0);

    TableWidget* tableWidget;
};

#endif // TABLEDIALOG_H
