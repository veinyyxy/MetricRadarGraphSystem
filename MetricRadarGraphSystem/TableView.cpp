#include "stdafx.h"
#include "TableView.h"


TableView::TableView()
{
	m_form.setupUi(this);
}


TableView::~TableView()
{
}

void TableView::AddTable(QWidget * pW, const QString strName)
{
	m_form.tabWidget->addTab(pW, strName);
}

void TableView::closeEvent(QCloseEvent * event)
{
	ChangeItem();
}
