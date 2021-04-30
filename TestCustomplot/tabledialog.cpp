#include "tabledialog.h"
#include <QBoxLayout>

TableDialog::TableDialog(QWidget *parent)
    : QDialog(parent)
{
    tableWidget = new TableWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableWidget);
    this->setLayout(mainLayout);
    this->resize(600,400);


}
