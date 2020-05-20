#pragma once
#include "qwt_scale_draw.h"
class TimeScaleDraw :
	public QwtScaleDraw
{
public:
	TimeScaleDraw(const QTime &base);
	virtual QwtText label(double v) const;
	
private:
	QTime baseTime;
};

