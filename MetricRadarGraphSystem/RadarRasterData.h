#pragma once
#include "qwt_matrix_raster_data.h"
#include "ParseData.h"

class RadarRasterData :
	public QwtMatrixRasterData
{
public:
	RadarRasterData();
	virtual ~RadarRasterData();
	void Make(ParseData* pPD);
	inline void SetFillValue(float fV) { m_fillValue = fV; }
	inline void SetMaxValue(float fV) { m_MaxValue = fV; }

private:
	float m_fillValue;
	float m_MaxValue;
};

