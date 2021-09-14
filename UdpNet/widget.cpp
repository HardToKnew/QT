#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QStatusBar>

Widget::Widget(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    info_lable = new QLabel;
    /*QStatusBar* status = new QStatusBar(this);
    status->addWidget(info_lable);*/
    info_lable->setText("send:    ");
    this->statusBar()->addWidget(info_lable);

    //ui->status
    //ui->statusBar()->addWidget();


    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress("192.168.0.250"),8080);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(realRead_slot()));
}

Widget::~Widget()
{
    delete ui;
}

int Widget::createRand()
{
    int m_rand;
    do{
        m_rand = rand();	// rand returns a number between 0 and 0x7FFF
    } while(m_rand == 0);    // make sure m_rand is not zero
    return m_rand;

}

int Widget::getRandPort()
{
    int m_Rand=0;
    do
    {
        m_Rand=(rand() % (65535-49152+1))+49152;
    }
    while(m_Rand<49152||m_Rand>65535);
    return m_Rand;

}
void Widget::on_openBt_clicked()
{

    if(!udpSocket->state())
    {
        QString qSlocalIP = ui->ipEdit_2->text();
        QHostAddress localIP = QHostAddress(qSlocalIP);
        quint16 port = getRandPort();
        //if (udpSocket->bind(ui->LocalPortEdit->text().toUInt()) == true){
        if (udpSocket->bind(QHostAddress(localIP),port) == true){
            ui->ipEdit_2->setText(localIP.toString());
            ui->ipEdit->setText(localIP.toString());
            ui->LocalPortEdit->setText(QString::number(port));
            QMessageBox::information(this,"提示","成功");
        }
        else
        {
            QMessageBox::information(this,"提示","失败");
        }
    }
    //connect(udpSocket,SIGNAL(readyRead()),this,SLOT(realRead_slot()));
}

void Widget::realRead_slot(){
    /*while (udpSocket->hasPendingDatagrams()) {
        QByteArray array;
        array.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(array.data(),array.size());
        QString buf;
        buf = array.data();
        //buf = QString(udpSocket->readAll());
        ui->recvEdit->appendPlainText(buf);
    }*/
    QHostAddress host;
    quint16 port;
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
            //char *buff = new char[1024];
        datagram.resize(udpSocket->pendingDatagramSize());
        int dataSize = udpSocket->readDatagram(datagram.data(),datagram.size(),&host,&port);
        if (dataSize!=-1)
        {
            QString buf = datagram.data();
            QString msg="[Receive from "+host.toString()+ ":" +QString::number(port)+"] Size: "+QString::number(dataSize)+"\n"+buf+"\n";
            ui->recvEdit->appendPlainText(msg);
            ui->ipEdit->setText(host.toString());
            ui->DestPortEdit->setText(QString::number(port));
        }
            //delete [] buff;
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
    info_lable->setText(QString("Send: "+QString::number(sendbuf.length())));
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
