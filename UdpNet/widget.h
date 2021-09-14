#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QUdpSocket>
#include <QString>
#include <QLabel>
#include <QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QMainWindow *parent = nullptr);
    ~Widget();

    QUdpSocket *udpSocket;

private slots:
    void on_openBt_clicked();
    void realRead_slot();

    void on_sendBt_clicked();

    void on_closeBt_clicked();

    void on_clearBt_clicked();

private:
    Ui::Widget *ui;
    QLabel *info_lable;

    int createRand();
    int getRandPort();
};
#endif // WIDGET_H
