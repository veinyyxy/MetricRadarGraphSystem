#include "stdafx.h"
#include "TimeScaleDraw.h"

TimeScaleDraw::TimeScaleDraw(const QTime & base) :
	baseTime(base)
{
}

QwtText TimeScaleDraw::label(double v) const
{
	QTime upTime = baseTime.addSecs((int)v*60.0);
	return upTime.toString("hh:mm");
}
