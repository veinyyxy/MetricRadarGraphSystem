#include "stdafx.h"
#include "CurveData.h"


CurveData::CurveData()
{
}


CurveData::~CurveData()
{
	for (size_t i = 0; i < m_ValueVector.size(); i++)
	{
		float* pValues = m_ValueVector[i];
		if(pValues != nullptr)
			delete[] pValues;
	}
}

void CurveData::AppendValueVector(float * pValues)
{
	m_ValueVector.push_back(pValues);
}
