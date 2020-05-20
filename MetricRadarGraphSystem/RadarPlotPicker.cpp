#include "stdafx.h"
#include "RadarPlotPicker.h"


RadarPlotPicker::RadarPlotPicker(QWidget *canvas) : QwtPlotPicker(canvas)
{
}

RadarPlotPicker::RadarPlotPicker(int xAxis, int yAxis, QWidget * canvas) : QwtPlotPicker(xAxis, yAxis, canvas)
{
}


RadarPlotPicker::RadarPlotPicker(int xAxis, int yAxis, RubberBand rubberBand
	, DisplayMode trackerMode, QWidget * canvas):QwtPlotPicker(xAxis, yAxis
		, rubberBand, trackerMode, canvas)
{
}

RadarPlotPicker::~RadarPlotPicker()
{
}

QwtText RadarPlotPicker::trackerText(const QPoint & point) const
{
	QwtText outText = QwtPlotPicker::trackerText(point);
	/*outText.setText("(" + outText.text());
	outText.setText(outText.text() + "(");*/
	QFont markFont;
	markFont.setBold(true);
	markFont.setPixelSize(18);
	outText.setFont(markFont);
	return outText;
}

QwtText RadarPlotPicker::trackerTextF(const QPointF & point) const
{
	emit CurrentPoint(point);

	QwtText outText;

	double value = 0;
	if (m_pMyData)
	{
		value = m_pMyData->value(point.x(), point.y());
	}

	QString strHeight = QString("%1").arg(point.y());
	QTime currentTime = m_StartTime.time().addSecs(point.x()*60.0);
	QString strTimeText = QString("%1").arg(currentTime.toString("hh:mm:ss.zzz"));
	outText.setText("[" + strTimeText + outText.text() + ", ");
	outText.setText(outText.text() + strHeight + " KM" + "] = " + QString("%1").arg(value));
	return outText;
}

void RadarPlotPicker::move(const QPoint & point)
{
	QwtPlotPicker::move(point);
}

void RadarPlotPicker::append(const QPoint & point)
{
	QwtPlotPicker::append(point);
}

bool RadarPlotPicker::end(bool ok)
{
	return QwtPlotPicker::end(ok);
}
