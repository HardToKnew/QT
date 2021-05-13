#include "BasicPlot.h"

struct BasicPlotPrivate
{
	Q_DECLARE_PUBLIC(BasicPlot)

	bool m_bTracerEnable = false;//�Ƿ�����tracer
	bool m_bTracerVisible = false;//�Ƿ���ʾtracer
	bool m_bAxisTipEnable = false;//�Ƿ���ʾ�������ϻ���
	bool m_bPriceVisible = false;//�Ƿ���ʾ�ּ���
	QCP::ViewType m_ePlotType;
	QCP::QuotaLineType m_eQuotaType;
	QCP::AxisRanges m_AutoRange = true;//�����᷶Χ�Զ�����
	QLabel * m_LeftAxisTip = nullptr;
	QLabel * m_RightAxisTip = nullptr;
	QLabel * m_BottomAxisTip = nullptr;

	CrossLinePlot * m_pCrossLine = nullptr;
	QVBoxLayout * m_pMainLayout = nullptr;

	BasicPlot * q_ptr;
	std::map<QCPGraph *, QCPItemTracer *> m_LineTracers;

	QCustomPlot * m_pPlot = nullptr;

	static std::map<QCPAxis::AxisType, std::vector<PlotCallback *>> m_BrotherAxisRange;

	struct RectRange
	{
		QCPRange left;
		QCPRange top;
		QCPRange bottom;
		QCPRange right;
	};
	static std::map<QCP::ViewType, RectRange> DefaultRange;

	QCPAxis * GetAxis(QCPAxis::AxisType axis);
};

