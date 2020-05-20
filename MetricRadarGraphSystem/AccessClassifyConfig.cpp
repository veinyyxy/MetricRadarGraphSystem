#include "stdafx.h"
#include "AccessClassifyConfig.h"


AccessClassifyConfig::AccessClassifyConfig()
{
}


AccessClassifyConfig::~AccessClassifyConfig()
{
}

int AccessClassifyConfig::ReadConfig(const QString& fileName, AccessClassifyConfig::ClassifyConfig* pCC)
{
	if (pCC == nullptr) return 0;
	QSettings configReader(fileName, QSettings::IniFormat);
	int type = configReader.value("TYPE/type").toInt();
	int classify_count = configReader.value("TYPE/classify_count").toInt();
	QString strNames = configReader.value("TYPE/classify_name").toString();

	pCC->raster_extends = configReader.value("TYPE/raster_extends").toString();
	pCC->curve_extends = configReader.value("TYPE/curve_extends").toString();

	QStringList nameList = strNames.split(";");

	QString strParennt = "CLASSIFY_%1";

	pCC->type = type;
	pCC->classify_count = classify_count;
	pCC->classify_name = nameList;

	for (int i = 0; i < classify_count; i++)
	{
		QString strKey = strParennt.arg(i + 1);
		QString strFileExtendName = configReader.value(strKey + QString::fromLocal8Bit("/extend")).toString();

		pCC->classify_extend.push_back(strFileExtendName);
	}

	configReader.beginGroup("SYMPLETABLE");
	QStringList keys = configReader.childKeys();
	configReader.endGroup();

	for (int i = 0; i < keys.size(); i++)
	{
		int iSympleKey = configReader.value("SYMPLETABLE/" + keys[i]).toInt();
		pCC->symbol_map.insert(keys[i], (QwtSymbol::Style)iSympleKey);
	}

	for (int i = 0; i < pCC->classify_extend.size(); i++)
	{
		QString extendname = pCC->classify_extend.at(i);

		QStringList strChildExtendName = extendname.split(";");
		for (int ii = 0; ii < strChildExtendName.size(); ii++)
		{
			QString strChildName = strChildExtendName.at(ii);
			QString strFormat = configReader.value("IMAGEFORMAT" + QString::fromLocal8Bit("/") + strChildName).toString();
			QString strRightName = configReader.value("RIGHTAXISTITLE" + QString::fromLocal8Bit("/") + strChildName).toString();
			QString strUIParameters = configReader.value("UIPARAMETER" + QString::fromLocal8Bit("/") + strChildName).toString();
			QString strExpression = configReader.value("EXPRESSION" + QString::fromLocal8Bit("/") + strChildName).toString();
			int iDelLable = configReader.value("DELETE_COLOR_MIN_LABLE" + QString::fromLocal8Bit("/") + strChildName).toInt();

			QStringList keyValuePair = strUIParameters.split(";");
			QMap<QString, QString> mapUIParameters;
			for (int iii = 0; iii < keyValuePair.size(); iii++)
			{
				QStringList KeyAndValue = keyValuePair[iii].split("=");
				if (KeyAndValue.size() > 1)
				{
					mapUIParameters.insert(KeyAndValue[0], KeyAndValue[1]);
				}
			}

			pCC->uiParameter.insert(strChildName, mapUIParameters);
			pCC->saveFileFormat.insert(strChildName, strFormat);
			pCC->rightAxisNames.insert(strChildName, strRightName);
			pCC->expression.insert(strChildName, strExpression);
			pCC->deleteMinLabel.insert(strChildName, iDelLable);
		}
		
	}
	return 1;
}
