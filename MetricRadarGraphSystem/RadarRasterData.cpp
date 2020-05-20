#include "stdafx.h"
#include "RadarRasterData.h"


RadarRasterData::RadarRasterData()
{
}

RadarRasterData::~RadarRasterData()
{
}

void RadarRasterData::Make(ParseData* pPD)
{
	float* data(pPD->GetData());
	uint uiSize(pPD->GetDataSize());
	int numColumns(pPD->GetDataColumnCount());
	float fXMin;
	float fXMax;
	float fYMin;
	float fYMax;
	float fZMin;
	float fZMax;
	pPD->GetAxisProperty(&fXMin, &fXMax, &fYMin, &fYMax, &fZMin, &fZMax);

	QVector<double> values;
	//for (uint i = 0; i < uiSize; i++)
	//{
	//	double fV = data[i];
	//	if (abs(abs(fV) - 0) < 0.000001)
	//	{
	//		values.push_back(-10.6);
	//	}
	//	else if (fV < -10.5)
	//	{
	//		values.push_back(-10.66);
	//		//continue;
	//	}
	//	else
	//	{
	//		values.push_back(fV);
	//	}
	//}
	//setValueMatrix(values, numColumns);

	
	int row = numColumns;
	int column = uiSize / numColumns;

	double* pTempBuffer = new double[column * row];
	memset(pTempBuffer, 0, sizeof(double) * column * row);

	for (int i = 0; i< row; i++)
	{
		for (int j = 0; j< column; j++)
		{
			double dValue = *(data + i * column + j);
			
			*(pTempBuffer + j * row + i) = dValue;
			//values.push_back(dValue);
		}
	}

	for (int i = 0; i < column*row; i++)
	{
		double dV = pTempBuffer[i];
		if (dV < fZMin)
		{
			values.push_back(m_fillValue);
		}
		else if(fZMax > fZMax)
		{
			values.push_back(m_MaxValue);
		}
		else
			values.push_back(dV);
	}

	setValueMatrix(values, row);

	
	std::string strXComment, strYComment;
	
	setInterval(Qt::XAxis,
		QwtInterval(fXMin, fXMax));
	setInterval(Qt::YAxis,
		QwtInterval(fYMin, fYMax));
	setInterval(Qt::ZAxis, QwtInterval(fZMin, fZMax));
}
