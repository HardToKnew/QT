#ifndef BASEPLOT_H
#define BASEPLOT_H

#include <QWidget>

#include "qcustomplot.h"

/// ������ͼ��ӿ���

struct PlotCallback
{
	virtual void SyncAxisRange(QCPAxis::AxisType type, const QCPRange & range) = 0;

	virtual bool TipLabelEnable() const = 0;
	virtual void MoveTipLabel(const QPoint & pos) = 0;

	virtual bool LineTracerEnable() const = 0;
	virtual void MoveLineTracer(const QPoint & pos) = 0;
};

#endif // BASEPLOT_H
