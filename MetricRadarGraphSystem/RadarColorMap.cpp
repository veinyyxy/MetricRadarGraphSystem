#include "stdafx.h"
#include "RadarColorMap.h"
#include "NonlinearityColorMap.h"
#define INDEX_TO_COLOR(mix, mid, max) (((mid)-(mix))/((max)-(mix)))

RadarColorMap::RadarColorMap() : m_pColorBar(0)
{
	
}

RadarColorMap::~RadarColorMap()
{
}

QwtColorMap*  RadarColorMap::Make(ColorBar* pCB)
{
	QwtColorMap* pColorMap = 0;

	std::vector<float> values;
	pCB->GetValueSet(&values);
	size_t valuesSize = values.size();

	if (pCB->GetBarStyle() == ColorBar::LINEAR)
	{
		QwtLinearColorMap* pLinearColorMap = new QwtLinearColorMap();
		pLinearColorMap->setMode(QwtLinearColorMap::FixedColors);
		float mixValue = 0;
		float maxValue = 0;

		if (valuesSize > 1)
		{
			mixValue = values[0];
			maxValue = values[values.size() - 1];
		}
		else
			return 0;

		for (size_t i = 0; i < valuesSize; i++)
		{
			float fCurrent = values[i];
			ColorBar::COLOR_UNIT colorUnit;
			pCB->GetColor(fCurrent, &colorUnit);
			pLinearColorMap->addColorStop(INDEX_TO_COLOR(mixValue, fCurrent, maxValue), QColor(colorUnit.fr, colorUnit.fg, colorUnit.fb));
		}
		m_min = mixValue;
		m_max = maxValue;
		m_setp = (m_max - m_min) / (valuesSize - 1);
		m_pColorBar = pCB;

		pColorMap = pLinearColorMap;
	}
	else
	{
#if 1
		NonlinearityColorMap* pNonlinearityColorMap = new NonlinearityColorMap();
		
		for (size_t i = 0; i < valuesSize; i++)
		{
			float fCurrent = values[i];
			QColor color;
			pCB->GetColor(fCurrent, &color);
			pNonlinearityColorMap->insertValueToColor(fCurrent, color);
		}

		m_min = values[0];
		m_max = values[valuesSize - 1];
		m_setp = (m_max - m_min) / (valuesSize - 1);

		pColorMap = pNonlinearityColorMap;
		m_pColorBar = pCB;
#else
		QwtLinearColorMap* pLinearColorMap = new QwtLinearColorMap();
		pLinearColorMap->setMode(QwtLinearColorMap::ScaledColors);
		float mixValue = 0;
		float maxValue = 0;

		if (valuesSize > 1)
		{
			mixValue = values[0];
			maxValue = values[values.size() - 1];
		}
		else
			return 0;

		for (size_t i = 0; i < valuesSize; i++)
		{
			float fCurrent = values[i];
			ColorBar::COLOR_UNIT colorUnit;
			pCB->GetColor(fCurrent, &colorUnit);
			pLinearColorMap->addColorStop(fCurrent, QColor(colorUnit.fr, colorUnit.fg, colorUnit.fb));
		}
		m_min = mixValue;
		m_max = maxValue;
		m_setp = (m_max - m_min) / (valuesSize - 1);
		m_pColorBar = pCB;

		pColorMap = pLinearColorMap;
#endif
	}

	return pColorMap;
}
