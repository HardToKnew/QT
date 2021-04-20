#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "tablewidget.h"


class MyDialog:public QDialog
{
    Q_OBJECT
public:
    MyDialog(QWidget *parent = 0);
    void showDialog();
    TableWidget *TableDialog;

};

#endif // MYDIALOG_H
