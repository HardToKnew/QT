#ifndef QCPCROSSLINE_H
#define QCPCROSSLINE_H

#include <QtCore/QString>

#include "QCustomplot.h"

namespace QCP
{
	enum LineState
	{
		E_NULL = 0x1,
		E_Vertical = 0x2,
		E_Horizontal = 0x4,
		E_ALL = E_Vertical + E_Horizontal
	};
	Q_DECLARE_FLAGS(LineStates, LineState);
}

class PlotCallback;

struct CrossLinePlotPrivate;

/// ������ʮ���߻����࣬�������ͬ��������ʮ����(ͨ��RegisiterBortherLine�ӿ�ʵ��)�����Ҹ���ͬ��ͼ���ϵ���ʾ������Ϣ��tracer��λ��

class CrossLinePlot : public  QCPLayerable
{
	Q_OBJECT
signals :
	void DrawCrossLine(const QPoint & pos);

public:
	CrossLinePlot(PlotCallback * basePlot, QCustomPlot * plot);
	~CrossLinePlot();

public:
	QString LayerName() const;
	void SetVisible(bool visible);//���ò��Ƿ����

	void SetPen(const QPen & pen);

	bool MouseButtonDown() const ;
	bool GetLineVisible(QCP::LineState line) const;
	void SetLineShow(QCP::LineState lines);

	//ʮ����ͬ��ע��ӿ�
	bool RegisiterBortherLine(CrossLinePlot * line);
	bool UnregisiterBortherLine(CrossLinePlot * line);

protected:
	virtual void applyDefaultAntialiasingHint(QCPPainter *painter) const{};
	virtual void draw(QCPPainter * painter);

private:
	void DrawLine(QCPAxis * axis, Qt::Orientation orientation);
	void SyncLinePosition(const QPoint & pos, double x);

private slots:
	void MouseMoveHandle(QMouseEvent * event);

private:
	QScopedPointer<CrossLinePlotPrivate> d_ptr;
	static std::vector<CrossLinePlot *> m_BrotherLine;
};

#endif // QCPCROSSLINE_H
