#include "stdafx.h"
#include "ConfigurableColorBar.h"


ConfigurableColorBar::ConfigurableColorBar()
{
}

ConfigurableColorBar::~ConfigurableColorBar()
{
}

void ConfigurableColorBar::LoadData(const std::string& strFile)
{
	QSettings configIniWrite(strFile.c_str(), QSettings::IniFormat);
	int iCount = configIniWrite.value("VALUE_COUNT/count").toInt();
	m_iType = configIniWrite.value("TYPE/section").toInt();
	for (int i = 0; i < iCount; i++)
	{
		QString strPath = "COLOR_MAP/pair" + QString("%1").arg(i + 1);
		QString strPair = configIniWrite.value(strPath).toString();
		QStringList strList = strPair.split(':');
		if (strList.length() > 1)
		{
			float fkey = strList[0].toFloat();
			QStringList strColor = strList[1].split(",");

			int iR, iG, iB;
			COLOR_UNIT cu;
			if (strColor.length() > 2)
			{
				iR = strColor[0].toInt();
				iG = strColor[1].toInt();
				iB = strColor[2].toInt();

				cu.fr = iR;
				cu.fg = iG;
				cu.fb = iB;
				cu.fa = 255;
			}

			m_ColorMap.insert(COLOR_PAIR(fkey, cu));
		}
	}
}

ColorBar::BarStyle ConfigurableColorBar::GetBarStyle()
{
	if (m_iType == 0)
		return ColorBar::LINEAR;
	else
		return ColorBar::NONLINEARITY;
}
