#ifndef GRAPHPLOT_H
#define GRAPHPLOT_H

#include <QWidget>

#include "PlotDefine.h"

#include "PlotCallback.h"

class QCustomPlot;

class CrossLinePlot;


/// ����������ͼ ֧�ֲ������ߡ���״ͼ��ɢ��  �����Ҫ�����߽��к�����������Ҫ�Լ���������ָ�룬����ֱ�ӵ�����ؽӿ�ֱ������
/// 1��ͼ����ˮƽ�ʹ�ֱ�������ʾ��Ϣ���Ǹ���ʮ���ߵĺ������Ƿ���ʾ����

namespace QCP
{
	Q_DECLARE_FLAGS(AxisRanges, AxisRange);
	Q_DECLARE_FLAGS(QuotaLineTypes, QuotaLineType);
}

struct BasicPlotPrivate;

class BasicPlot : public QWidget
	, public PlotCallback
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(BasicPlot)

protected:
	BasicPlot(QWidget * parent = nullptr);
public:
	~BasicPlot();

public:
	//����ͼ����
	QCPGraph * GetGraph(int index) const;
	QCPGraph * GetGraph() const;
	QCPGraph * AddGraph(QCPAxis * keyAxis = 0, QCPAxis * valueAxis = 0);
	bool RemoveGraph(QCPGraph * graph);
	bool RemoveGraph(int index);
	bool RemoveGraph(const QString & name);
	int ClearGraphs();
	int GraphCount() const;
	QList<QCPGraph *> SelectedGraphs() const;
	//������������

//	void SetGraphData(const std::vector<stock::LineData> & datas, QCPGraph * graph = nullptr);
	void SetGraphData(const std::vector<double> & key, const std::vector<double> & value, QCPGraph * graph = nullptr);
	void AddPointData(double key, double value, QCPGraph * graph = nullptr);//���� �����Զ���key���򣬿��Դ��ڶ��key���������ڸ�������

	//��״ͼ����
	QCPBars * AddBars(QCPAxis * keyAxis = 0, QCPAxis * valueAxis = 0);
	//��״ͼ�������
//	void SetBarsData(const std::vector<stock::LineData> & datas, QCPBars * bars = nullptr);
	void SetBarsData(const std::vector<double> & key, const std::vector<double> & value, QCPBars * bars = nullptr);
	void AddBarData(double key, double value, QCPBars * bars = nullptr);//���� �����Զ���key���򣬿��Դ��ڶ��key���������ڸ�������

	bool RemovePlottable(QCPAbstractPlottable * plottable);
	bool RemovePlottable(const QString & name);

	//ͼ������
	void SetPlotType(QCP::ViewType type);
	QCP::ViewType GetPlotType() const;

	//ָ�����ͣ���ͼ������Ϊ��ʱ���ýӿڲ�����
	void SetQuotaType(QCP::QuotaLineType type);
	QCP::QuotaLineType GetQuotaType() const;
	
	//�����᷶Χ
	void SetAxisLower(QCPAxis::AxisType type, double lower);
	void SetAxisUpper(QCPAxis::AxisType type, double upper);
	void SetAxisRange(QCPAxis::AxisType type, double lower, double upper);

public:
	//������������ʾ��ʽ
	void SetAxisLabelFormat(QCPAxis::AxisTypes axse, const QString & format);
	void SetAxisLabelPrecision(QCPAxis::AxisTypes axse, int precision);
	void ResetPlot();//����ͼ��

public:
	//BasePlot
	virtual void SyncAxisRange(QCPAxis::AxisType type, const QCPRange & range) override; 
	virtual bool TipLabelEnable() const override;
	virtual void MoveTipLabel(const QPoint & pos) override;
	virtual bool LineTracerEnable() const override;
	virtual void MoveLineTracer(const QPoint & pos) override;

	void SetLineTracerEnable(bool enable);//�Ƿ�����tracer
	void SetLineTracerVisible(bool visible, QCPGraph * graph = nullptr);//����ƶ�ʱ������ͼ�ϵ�С���Ƿ���ʾ
	void SetMoveTipLabel(bool enable);//�Ƿ�����ʮ���߶��˵Ļ���
	void SetToopTipVisible(QCPAxis::AxisTypes axse, bool visible);

	//�����᷶Χ�Ƿ��Զ�����
	void SetAutoAxisRange(QCP::AxisRange type, bool enable);
	void SetAutoAxisRange(QCP::AxisRanges axse);

	//���ýڵ�����չʾ���ͣ����磺����Բ�������ε�
	void SetScatterStyle(QCPScatterStyle style, QCPGraph * graph = nullptr);

	//ʮ����ͬ��
	void SetCrossLineVisible(bool visible);
	CrossLinePlot * GetCrossLine() const;
	bool RegisiterBortherLine(CrossLinePlot * line);
	bool UnregisiterBortherLine(CrossLinePlot * line);

	QCPAxis * GetAxis(QCPAxis::AxisType axis);
	void SetGridVisible(bool visible);
	void SetAxisPen(QCPAxis::AxisTypes axse, const QPen & pen);
	void SetAxisPadding(QCPAxis::AxisType type, int padding);

protected:
	virtual void enterEvent(QEvent * event) override;
	virtual void leaveEvent(QEvent * event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;//��ʱ���ᱻִ�� �������Ӵ���(QCustomPlot)���¼�ѭ���ж�

protected:
	BasicPlot(BasicPlotPrivate & pd, QWidget * parent = nullptr);

protected:
	void EnableFixedTicker(QCPAxis::AxisTypes axse);

private:
	void InitializeUI();

protected:
	QScopedPointer<BasicPlotPrivate> d_ptr;

	friend class CrossLinePlot;
};

#endif // GRAPHPLOT_H
