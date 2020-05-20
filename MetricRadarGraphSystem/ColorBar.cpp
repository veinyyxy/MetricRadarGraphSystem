#include "stdafx.h"
#include "ColorBar.h"


ColorBar::ColorBar()
{
}


ColorBar::~ColorBar()
{
}

int ColorBar::GetValueSet(std::vector<float>* pSet)
{
	int iReslut = 0;
	COLOR_MAP_INTERATOR be = m_ColorMap.begin();
	while (be != m_ColorMap.end())
	{
		iReslut = 1;
		pSet->push_back(be->first);
		be++;
	}

	return iReslut;
}

int ColorBar::GetColor(float fV, ColorBar::COLOR_UNIT* pColor)
{
	COLOR_MAP_INTERATOR result = m_ColorMap.find(fV);
	if (result != m_ColorMap.end())
	{
		*pColor = result->second;
		return 1;
	}
	else
		return 0;
}

int ColorBar::GetColor(float fV, QColor* pColor)
{
	ColorBar::COLOR_UNIT color;
	if (GetColor(fV, &color))
	{
		pColor->setRed(color.fr);
		pColor->setBlue(color.fb);
		pColor->setGreen(color.fg);
		pColor->setAlpha(color.fa);
		return 1;
	}
	else
		return 0;
}
