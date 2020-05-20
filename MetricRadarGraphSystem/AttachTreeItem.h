#pragma once
class AttachTreeItem
{
public:
	AttachTreeItem();
	~AttachTreeItem();
	/*inline void SetIndex(const QModelIndex& mi) {
	m_ModelIndex = mi;
	}*/
	inline void SetItem(QStandardItem* pItem) { m_pStandardItem = pItem; }
	void ChangeItem();
	//inline void SetRowNum(int iR) { m_iRow = iR; }
	//inline void SetModel(QAbstractItemModel* pModel) { m_pItemModel = pModel; }
	//inline void SetStationName(const QString& name) { m_strStationName = name; }
private:
	QStandardItem* m_pStandardItem;
	//QModelIndex m_ModelIndex;
	//int m_iRow;
	//QAbstractItemModel* m_pItemModel;
	//QString m_strStationName;
};

