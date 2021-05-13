#ifndef QCPAXISTICKERPIXEL_H
#define QCPAXISTICKERPIXEL_H

#include "QCustomplot.h"

struct AxisFixedPixelTickerPrivate;

/// ���������ƻ������ᣬʵ���˹̶����أ�ʹ��setTickPixelStep�ӿ�����

class AxisFixedPixelTicker : public QCPAxisTicker
{
public:
	AxisFixedPixelTicker(QCPAxis * axis);
	~AxisFixedPixelTicker();

public:
	void SetTickPixelStep(int pixel);
	int GetTickPixelStep() const;

protected:
	//QCPAxisTicker
	virtual double getTickStep(const QCPRange & range) override;

private:
	QScopedPointer<AxisFixedPixelTickerPrivate> d_ptr;
};

#endif // QCPAXISTICKERPIXEL_H
