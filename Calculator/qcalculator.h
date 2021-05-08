#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include "qcalculatorui.h"
#include "qcalculatordec.h"
class QCalculator
{
/*public:
    QCalculator();*/
protected:
    QCalculatorUI* m_ui;
    QCalculatorDec m_cal;

    QCalculator();
    bool construct();
public:
    static QCalculator* NewInstance();
    void show();
    ~QCalculator();

};

#endif // QCALCULATOR_H
