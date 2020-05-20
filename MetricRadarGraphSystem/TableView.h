#pragma once
#include "ui_TableView.h"
#include "AttachTreeItem.h"

class TableView :
	public QWidget, public AttachTreeItem
{
public:
	TableView();
	~TableView();
	void AddTable(QWidget* pW, const QString strName);

	Ui::Form m_form;
	void closeEvent(QCloseEvent *event);
};

