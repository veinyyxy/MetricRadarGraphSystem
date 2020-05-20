#pragma once
#include "ColorBar.h"
class ConfigurableColorBar :
	public ColorBar
{
public:
	ConfigurableColorBar();
	virtual ~ConfigurableColorBar();
	virtual void LoadData(const std::string& strFile);
	virtual ColorBar::BarStyle GetBarStyle();
private:
	int m_iType;
};

