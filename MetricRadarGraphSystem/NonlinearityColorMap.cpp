#include "stdafx.h"
#include "NonlinearityColorMap.h"


NonlinearityColorMap::NonlinearityColorMap() : QwtColorMap(QwtColorMap::RGB)
{
	
}


NonlinearityColorMap::~NonlinearityColorMap()
{
}

QRgb NonlinearityColorMap::rgb(const QwtInterval & interval, double value) const
{
	
	for (int i = 1; i < m_Value.size(); i++)
	{
		double minValue = m_Value.at(i - 1);
		double maxValue = m_Value.at(i);
		if ((value >  minValue && value < maxValue) || abs(value - maxValue) < 0.00001 )
		{
			return m_Color[i - 1].rgb();
		}
		else if(value < m_Value[0])
		{
			return m_Color[0].rgb();
		}
		else if (value > m_Value[m_Value.size() - 1])
		{
			return m_Color[m_Value.size() - 1].rgb();
		}
	}
	return m_Color[0].rgb();
}

unsigned char NonlinearityColorMap::colorIndex(const QwtInterval & interval, double value) const
{
	return 0;
}

void NonlinearityColorMap::insertValueToColor(double dValue, const QColor & color)
{
	m_Value.push_back(dValue);
	m_Color.push_back(color);
}
