#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress("192.168.0.250"),8080);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(realRead_slot()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openBt_clicked()
{
    //if (udpSocket->bind(ui->LocalPortEdit->text().toUInt()) == true){
    if (udpSocket->bind(QHostAddress("192.168.0.25"),8080) == true){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::information(this,"提示","失败");
    }
    //connect(udpSocket,SIGNAL(readyRead()),this,SLOT(realRead_slot()));
}

void Widget::realRead_slot(){
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray array;
        array.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(array.data(),array.size());
        QString buf;
        buf = array.data();
        //buf = QString(udpSocket->readAll());
        ui->recvEdit->appendPlainText(buf);
    }
}

void Widget::on_sendBt_clicked()
{
    quint16 port;

    QString sendbuf;

    QHostAddress address;

    address.setAddress(ui->ipEdit->text());
    sendbuf = ui->sendEdit->toPlainText();
    port = ui->DestPortEdit->text().toUInt();
    udpSocket->writeDatagram(sendbuf.toUtf8().data(),sendbuf.length(),address,port);

}

void Widget::on_closeBt_clicked()
{
    udpSocket->close();
}

void Widget::on_clearBt_clicked()
{
    ui->recvEdit->clear();
}
