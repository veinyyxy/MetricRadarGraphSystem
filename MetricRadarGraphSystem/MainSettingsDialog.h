#pragma once
#include "qdialog.h"
#include "ui_MainSetting.h"
class MainSettingsDialog :
	public QDialog
{
public:
	MainSettingsDialog();
	~MainSettingsDialog();
	Ui::MainSettingDialogSetup m_setup;
};

