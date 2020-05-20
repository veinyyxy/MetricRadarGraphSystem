#pragma once
#include "qwt_color_map.h"
class NonlinearityColorMap :
	public QwtColorMap
{
public:
	NonlinearityColorMap();
	~NonlinearityColorMap();

	// Inherited via QwtColorMap
	virtual QRgb rgb(const QwtInterval & interval, double value) const override;
	virtual unsigned char colorIndex(const QwtInterval & interval, double value) const override;
	virtual void insertValueToColor(double dValue, const QColor& color);
private:
	QVector<double> m_Value;
	QVector<QColor> m_Color;
};

