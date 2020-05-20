#pragma once
#include "qwidget.h"
#include "AttachTreeItem.h"

class SubWindow :
	public QWidget, public AttachTreeItem
{
public:
	SubWindow();
	~SubWindow();
	void closeEvent(QCloseEvent *event);
	inline QWidget* GetMainWidget() { return m_PlotWidget; }
	inline void SetMainWidget(QWidget* pW) { m_PlotWidget = pW; }

private:
	QWidget* m_PlotWidget;
};

