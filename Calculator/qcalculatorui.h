#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "ICalculator.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_edit;
    QPushButton* m_buttons[20];
    ICalculator* m_cal; // UI通过接口指针保存业务逻辑相关类对象的地址，当通过setCalculator设置关联后即可通过接口使用业务逻辑提供的函数

    QCalculatorUI();
    bool construct();
private slots:
    void onButtonClicked();
public:
    static QCalculatorUI* NewInstance();
    void show();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
    ~QCalculatorUI();
};


#endif // QCALCULATORUI_H
