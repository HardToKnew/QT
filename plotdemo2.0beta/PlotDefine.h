#ifndef PlotDefine_h__
#define PlotDefine_h__

namespace QCP
{
	enum AxisRange
	{
		AR_LEFT,
		AR_RIGHT,
		AR_TOP,
		AR_BOTTOm,
		AR_NULL,
		AR_ALLAxis,
	};

	enum ViewType
	{
		EVT_NULL,
		EVT_TIME_DAY_1,
		EVT_TIME_DAY_5,
		EVT_KLINE_DAY,
		EVT_KLINE_WEEK,
		EVT_KLINE_MONTH,
	};

	enum QuotaLineType
	{
		QT_NULL,

		//��ʱָ��
		QT_TIME,               // ��ʱ��
		QT_AVERAGE,               // ����
		QT_VOL,
		QT_LMR,//����

		//k��ָ��
		QT_KLINE,
		QT_MACD,
		QT_KDJ,
		QT_RSI,
		QT_ARBR,
		QT_DMI,
		QT_CR,
		QT_PSY,
		QT_KD,
		QT_DMA,
	};
	Q_DECLARE_FLAGS(QuotaLineTypes, QuotaLineType);

	enum PlotElementKind
	{
		PEK_BAR,//��״ͼ
		PEK_GRAPH,//ͼͨ����ͼ
		PEK_GRAPH2,//���л�ˢ����ͼ
		PEK_GRAPH3,//��ǰ�㻭��ֱ�ߵ�x������ͼ
		PEK_GRAPH4,//ԲȦ����ͼ
		PEK_AREA,//���ͼ
		PEK_FINACIAL,//ʵ��ͼ
	};
}
#endif // PlotDefine_h__