#include "mydialog.h"
#include <QPushButton>

MyDialog::MyDialog(QWidget *parent )
    :QDialog(parent)
{
    //QPushButton *ok=new QPushButton(this);
    //ok->setText("ok");
    TableDialog=new TableWidget(this);
    QHBoxLayout *mainLayout=new QHBoxLayout;
    this->setLayout(mainLayout);
    mainLayout->addWidget(TableDialog);


}

void MyDialog::showDialog()
{
    this->show();
    TableDialog->showAddEntryDialog();
}
