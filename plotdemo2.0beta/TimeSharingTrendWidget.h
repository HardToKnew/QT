#ifndef TIMESHARINGTRENDWIDGET_H
#define TIMESHARINGTRENDWIDGET_H

#include <QWidget>

#include "BasicPlot.h"
#include "BasicWidget.h"


struct TimeSharingTrendWidgetPrivate;

class TimeSharingTrendPlot;


/// ��������ʱͼ�����࣬�ڲ�Ƕ��TimeSharingTrendPlot��ͼ�齨�����н������ݵ�����������ֱ�ӱ�ʹ�û������PlotWidgetʹ��

class TimeSharingTrendWidget : public BasicWidget//, public stock::ITimeLineObserve
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(TimeSharingTrendWidget)

public:
	TimeSharingTrendWidget(QWidget * parent = nullptr);
	~TimeSharingTrendWidget();

public:	
	//ͼ������
// 	void SetPlotType(stock::TViewType type);
// 	stock::TViewType GetPlotType() const;
// 
// 	//ָ�����ͣ���ͼ������Ϊ��ʱ���ýӿڲ�����
// 	void SetQuotaType(stock::TLineQuotaType type);
// 	stock::TLineQuotaType GettQuotaType() const;

	TimeSharingTrendPlot * GetTimeSharingTrendPlot() const;
	virtual void SetPresentPriceVisible(bool visible) override;

protected:
	//stock::ITimeLineObserve
	//virtual void OnUpdate2(const stock::TLineQuotaType & type, const DataContainer<stock::LineData> & data) override;

private:
	void InitializeUI();
	void DisposeQuotaData(QCP::QuotaLineType type);

private:
};

#endif // TIMESHARINGTRENDWIDGET_H
