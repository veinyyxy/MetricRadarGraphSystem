#include "stdafx.h"
#include "ParseRasterFile.h"


ParseRasterFile::ParseRasterFile()
{
}

ParseRasterFile::~ParseRasterFile()
{
}

bool ParseRasterFile::ReadDataFromFile(const std::string& strFielName)
{
	P_FILE_HEADER fh = new FILE_HEADER;
	memset(fh, 0, sizeof(FILE_HEADER));
	QFile file(strFielName.c_str());
	if (!file.open(QIODevice::ReadOnly))
	{
		delete fh;
		return false;
	}
	uint size = sizeof(FILE_HEADER);
	QDataStream out(&file);
	out.readRawData((char*)fh, size);

	m_ColumnCount = fh->Num_beam;
	//out.read
	char* recordTime = new char[fh->Num_beam * 20];
	out.readRawData(recordTime, fh->Num_beam * 20);
	m_OtherData = new ParseData::AdditionalData;
	m_OtherData->buffer = recordTime;
	m_OtherData->size = fh->Num_beam * 20;

	m_DataSize = fh->Num_beam * fh->Num_gate;
	uint dataSizeForBytes = m_DataSize * sizeof(float);
	m_pData = new float[m_DataSize];
	memset(m_pData, 0, dataSizeForBytes);

	out.readRawData((char*)m_pData, dataSizeForBytes);

	if (m_strExpression.size() != 0)
	{
		if (m_strExpression == QString::fromLocal8Bit("log10"))
		{
			for (size_t i = 0; i < m_DataSize; i++)
			{
				if (abs(*(m_pData + i) - (-32768)) < 0.0001)
				{
					continue;
				}
				else
					*(m_pData + i) = log10f(*(m_pData + i));
			}
		}
	}

	char pXComment[21] = { 0 };
	memcpy_s(pXComment, 20, recordTime, 20);

	QString strComment = pXComment;
	//strComment =  strComment;
	SetAxisComment(strComment.toStdString(), "Height(km)", "");
	
	m_strStationName = QString::fromLocal8Bit(fh->radar_name);

	delete fh;
	return true;
}

bool ParseRasterFile::ReadDataFromMemory(const void* pData)
{
	return false;
}

ParseData::DataType ParseRasterFile::GetDataType()
{
	return ParseData::RASTER;
}