#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QHostInfo>
#include <QDebug>
#include <QNetworkInterface>
#include <QList>

#define Col1 0
#define Col2 1

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setWindowTitle("CSDN IT1995");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setRowCount(255);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
}

Widget::~Widget()
{
    delete ui;
}

int useRow = 0;

void Widget::lookUp(const QHostInfo &host)
{
    if(host.error() != QHostInfo::NoError){

        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    if(host.addresses()[0].toString() == host.hostName())
        return;

    QTableWidgetItem *ipItem = new QTableWidgetItem;
    ipItem->setText(host.addresses()[0].toString());
    QTableWidgetItem *hostItem = new QTableWidgetItem;
    hostItem->setText(host.hostName());


    if(ipItem->text() != hostItem->text()){

        ipItem->setTextColor(QColor(Qt::red));
        hostItem->setTextColor(QColor(Qt::red));
    }
    ui->tableWidget->setItem(useRow, Col1, ipItem);
    ui->tableWidget->setItem(useRow, Col2, hostItem);
    useRow++;
}

void Widget::btnClicked()
{
    for(int i = 1 ; i < 256; i++){

        QHostInfo::lookupHost(QString("192.168.1.%1").arg(i), this, SLOT(lookUp(QHostInfo)));
    }
    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        //设备名
        qDebug() << "Device:" << netInterface.name();

        //MAC地址
        qDebug() << "HardwareAddress:" << netInterface.hardwareAddress();

        /*QList entryList = netInterface.addressEntries();

        //遍历每一个IP地址(每个包含一个IP地址，一个子网掩码和一个广播地址)
        foreach(QNetworkAddressEntry entry, entryList)
        {
            //IP地址
            qDebug() << "IP Address:" << entry.ip().toString();

            //子网掩码
            qDebug() << "Netmask:" << entry.netmask().toString();

            //广播地址
            qDebug() << "Broadcast:" << entry.broadcast().toString();
        }*/
    }
}
