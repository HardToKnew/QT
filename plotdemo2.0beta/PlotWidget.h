#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <memory>
#include <functional>

#include <QtGui/QColor>

#include <QtWidgets/QWidget>

#include "PlotDefine.h"

namespace QCP
{
//	Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::WindowFlags);

	enum WindowFlag	{
		NOTHING = 0,
		TITLE = 0x1,//������
		AVARGE = TITLE * 2,//����
		QUOTAS = AVARGE * 2,//ָ�꼯��k�ߺ�k��ָ��ֱ�ӵ�в�ͬ��ָ����
		ZOOM_OUT = QUOTAS * 2,
		ZOOM_IN = ZOOM_OUT * 2,
		SETUP = ZOOM_IN * 2,
		FRUSH = SETUP * 2,
		CLOSE = FRUSH * 2,

		TIMESHARING = TITLE | AVARGE | FRUSH | ZOOM_OUT | ZOOM_IN,//��ʱ��ݴ�������
		KLINE = QUOTAS | ZOOM_OUT | ZOOM_IN | SETUP | FRUSH,//k�߿�ݴ�������
		QUOTA = QUOTAS | SETUP | CLOSE,//k��ָ���ݴ�������
	};

	Q_DECLARE_FLAGS(WindowFlags, WindowFlag);
};

struct QuotaItemPrivate;


/// ������ָ��С��Ŀ

class QuotaItem : public QWidget
{
	Q_OBJECT

signals:
	void ItemClicked(QCP::QuotaLineType id, bool visible);

public:
	//quotaָ�����ƣ���ΪΨһid����֧���޸�
	QuotaItem(QCP::QuotaLineType id, double value, QWidget * parent = nullptr);
	~QuotaItem();


public:
	const QString & QuotaName() const;
	void SetValue(double value);
	double GetValue() const;
	void SetTextColor(const QColor & color);
	const QColor & GetTextColor() const;

private:
	QScopedPointer<QuotaItemPrivate> d_ptr;
};

struct PlotWidgetPrivate;

class BasicWidget;


/// ��������װ�˴��б������Ĵ��ڣ���Ҫ����չʾͼ���ڣ�ʹ��SetContentWidget�ӿڽ���ͼ��������
/// ע�⣺����ֱ��Ƕ���ͼ�齨������TimeSharingTrendPlot����Ϊ��ͼ�齨û���վݽ������������Խ������������Ĵ�����TimeSharingTrendWidget

class PlotWidget : public QWidget
{
	Q_OBJECT

signals:
	void AddQuotaSignal(QCP::QuotaLineType id);
	void ShowQuotaSignal(QCP::QuotaLineType id, bool);
	void RemoveQuotaSignal(QCP::QuotaLineType id);

public:
	PlotWidget(QWidget * parent = nullptr, QCP::WindowFlags flags = QCP::KLINE);
	~PlotWidget();

public:
	void SetTitleName(const QString & name);
	void SetAvarageName(const QString & name);
	void SetContentWidget(BasicWidget * widget);
	void RegisterToolBarCallback(std::function<void (QCP::WindowFlag flag)> & onclicked);

	QuotaItem * AddQuota(QCP::QuotaLineType id, double value);
	bool RemoveQuota(QCP::QuotaLineType id);
	bool SetQuotaValue(QCP::QuotaLineType id, double value);
	QColor GetQuotaColor(QCP::QuotaLineType id) const;

private slots:
	void ToobarButtonClicked(int);

private:
	void InitializeUI();
	void SetupTitile();
	void SetupContentWidget();

private:
	QScopedPointer<PlotWidgetPrivate> d_ptr;
};

#endif // PLOTWIDGET_H
