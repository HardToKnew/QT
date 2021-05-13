#ifndef MUTIAXESPLOT_H
#define MUTIAXESPLOT_H

#include <memory>

#include "FinancialPlot.h"

struct TimeSharingTrendPlotPrivate;


/// ����������ͼ����Ҫ����չʾ��ʱͼ��ͼ���п��԰���������ᣬ����ֻ��һ������


class TimeSharingTrendPlot : public FinancialPlot
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(TimeSharingTrendPlot)

protected:
	TimeSharingTrendPlot(QWidget * parent = nullptr);
public:
	~TimeSharingTrendPlot();

public:
	//ָ�����
	QCPBars * ShowVOL(bool visible);//
	QCPGraph * ShowLMR(bool visible);//����

protected:
	TimeSharingTrendPlot(TimeSharingTrendPlotPrivate & pd, QWidget * parent = nullptr);


	friend class TimeSharingTrendWidgetPrivate;
};

#endif // MUTIAXESPLOT_H
