#include "stdafx.h"
#include "AttachTreeItem.h"


AttachTreeItem::AttachTreeItem() : m_pStandardItem(nullptr)/*, m_pItemModel(nullptr), */
{
}

AttachTreeItem::~AttachTreeItem()
{
}

void AttachTreeItem::ChangeItem()
{
	//m_pItemModel->removeRow(m_iRow, m_ModelIndex);
	if (m_pStandardItem == nullptr) return;

	QJsonObject jsonValue = m_pStandardItem->data().toJsonObject();
	QJsonValue openState(false);
	jsonValue.insert("state", "false");

	m_pStandardItem->setData(jsonValue);
	m_pStandardItem->setIcon(QIcon("./icon/close.png"));

	//BasicPlot::closeEvent(event);
}
