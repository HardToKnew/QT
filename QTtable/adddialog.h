#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QDialog>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class adddialog:public QDialog
{
    Q_OBJECT
public:
    adddialog(QWidget *parent = 0);
public:
    //AddDialog(QWidget *parent = 0);
    QLineEdit *startText;
    QLineEdit *endText;
    QLineEdit *fhwmText;
    QLineEdit *netAreaText;
    QLineEdit *grossAreaText;
    QLineEdit *centroidText;
    QLineEdit *uncertaintyText;


private:
    QLabel *startLabel;
    QLabel *endLabel;
    QLabel *fhwmLabel;
    QLabel *netAreaLabel;
    QLabel *grossAreaLabel;
    QLabel *centroidLabel;
    QLabel *uncertaintyLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
