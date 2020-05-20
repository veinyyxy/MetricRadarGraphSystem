#include "stdafx.h"
#include "ParseData.h"


ParseData::ParseData() : 
	m_fXMin(0),
	m_fXMax(0),
	m_fYMin(0),
	m_fYMax(0),
	m_fZMin(0),
	m_fZMax(0), 
	m_OtherData(0)
{
	if (m_pData != nullptr)
	{
		delete[] m_pData;
	}

	if (m_OtherData != nullptr)
	{
		delete[] m_OtherData->buffer;
	}
}


ParseData::~ParseData()
{
	m_pData = nullptr;
	m_ColumnCount = 0;
}
