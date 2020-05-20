#pragma once
class AccessClassifyConfig
{
public:
	struct ClassifyConfig
	{
		int type;
		int classify_count;
		QString raster_extends;
		QString curve_extends;
		QStringList classify_name;
		QStringList classify_extend;
		QMap<QString, QwtSymbol::Style> symbol_map;
		QMap<QString, QString> saveFileFormat;
		QMap<QString, QString> rightAxisNames;
		QMap<QString, QString> expression;
		QMap<QString, QMap<QString, QString>> uiParameter;
		QMap<QString, int> deleteMinLabel;
	};

public:
	AccessClassifyConfig();
	virtual ~AccessClassifyConfig();
	int ReadConfig(const QString& fileName, AccessClassifyConfig::ClassifyConfig* pCC);
};

