#pragma once
#include "qwt_color_map.h"
#include "ColorBar.h"
class RadarColorMap
{
public:
	RadarColorMap();
	virtual ~RadarColorMap();
	QwtColorMap* Make(ColorBar* pCB);
	inline float GetMin() { return m_min; }
	inline float GetMax() { return m_max; }
	inline float GetSetp() { return m_setp; }
	inline ColorBar* GetColorBar() {
		return m_pColorBar
			;
	}
private:
	ColorBar* m_pColorBar;
	float m_min;
	float m_max;
	float m_setp;
};

