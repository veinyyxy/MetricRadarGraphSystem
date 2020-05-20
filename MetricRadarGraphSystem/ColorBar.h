#pragma once
class ColorBar
{
public:
	enum BarStyle { LINEAR, NONLINEARITY};
	
	struct COLOR_UNIT
	{
		int fr, fg, fb, fa;
	};

	typedef std::map<float, ColorBar::COLOR_UNIT> COLOR_MAP, *P_COLOR_MAP;
	typedef std::pair<float, ColorBar::COLOR_UNIT> COLOR_PAIR;
	typedef COLOR_MAP::iterator COLOR_MAP_INTERATOR, *P_COLOR_MAP_INTERATOR;

	ColorBar();
	virtual ~ColorBar();
	virtual void LoadData(const std::string& strFile) = 0;
	virtual ColorBar::BarStyle GetBarStyle() = 0;
	inline int GetColorCount() { return m_ColorCount; }
	int GetValueSet(std::vector<float>* pSet);
	int GetColor(float fV, ColorBar::COLOR_UNIT* pColor);
	int GetColor(float fV, QColor* pColor);
protected:
	ColorBar::COLOR_MAP m_ColorMap;
	int m_ColorCount;
	BarStyle m_Style;
};
