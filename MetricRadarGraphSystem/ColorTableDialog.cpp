#include "stdafx.h"
#include "ColorTableDialog.h"


ColorTableDialog::ColorTableDialog()
{
	m_setup.setupUi(this);

	QStringList headerList;
	headerList.push_back(QString::fromLocal8Bit("值"));
	headerList.push_back(QString::fromLocal8Bit("颜色"));
	headerList.push_back(QString::fromLocal8Bit("颜色值"));

	m_setup.tableWidget->setGridStyle(Qt::SolidLine);

	m_setup.tableWidget->setColumnCount(3);
	//m_setup.tableWidget->setRowCount(1);
	m_setup.tableWidget->setHorizontalHeaderLabels(headerList);

	m_setup.tableWidget->setColumnWidth(0, 100);
	m_setup.tableWidget->setColumnWidth(2, 200);
	m_setup.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	m_setup.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	m_setup.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	m_setup.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	m_setup.tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	//m_setup.tableWidget->
	connect(m_setup.tableWidget, SIGNAL(cellDoubleClicked(int, int)), SLOT(slot_cellDoubleClicked(int, int)));
	connect(m_setup.tableWidget, SIGNAL(cellClicked(int, int)), SLOT(slot_cellClicked(int, int)));
	connect(m_setup.tableWidget, SIGNAL(cellChanged(int, int)), SLOT(slot_cellChanged(int, int)));
	connect(m_setup.pushButton, SIGNAL(clicked(bool)), SLOT(slot_save(bool)));
	connect(m_setup.pushButton_2, SIGNAL(clicked(bool)), SLOT(slot_open(bool)));
	this->setWindowTitle(QString::fromLocal8Bit("创建颜色表"));
}

ColorTableDialog::~ColorTableDialog()
{
}

void ColorTableDialog::keyPressEvent(QKeyEvent * e)
{
	int iKey = e->key();
	switch (iKey)
	{
	case Qt::Key_Return:
	case Qt::Key_Enter:
	{
		int iIndex = m_setup.tableWidget->rowCount();
		m_setup.tableWidget->insertRow(iIndex);
		m_setup.tableWidget->setItem(iIndex, 0, new QTableWidgetItem());
		QTableWidgetItem* pColorItem = new QTableWidgetItem();
		pColorItem->setBackground(QColor(255,255,255));
		m_setup.tableWidget->setItem(iIndex, 1, pColorItem);
		m_setup.tableWidget->setItem(iIndex, 2, new QTableWidgetItem());
	}
		break;
	case Qt::Key_Delete:
	{
		int iCurrentRow = m_setup.tableWidget->currentRow();
		if (iCurrentRow >= 0)
			m_setup.tableWidget->removeRow(iCurrentRow);
	}
		break;
	default:
		break;
	}
}

void ColorTableDialog::slot_clickView()
{
	
}

void ColorTableDialog::slot_save(bool)
{
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/color_table_dir").toString();
	QString fileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存颜色表"), strDefalutOpenDir + "/colortable.ini", "*.ini");

	if (fileName.size() != 0)
	{
		QSettings colorTable(fileName, QSettings::IniFormat);
		colorTable.clear();

		if (m_setup.NoLinerCheckBox->isChecked())
		{
			colorTable.setValue("TYPE/section", 1);
		}
		else
		{
			colorTable.setValue("TYPE/section", 0);
		}

		int iCount = m_setup.tableWidget->rowCount();
		
		int iSure = 1;
		QString strFormat = "%1 : %2";
		for (int i = 0; i < iCount; i++)
		{
			QTableWidgetItem* pItem0 = m_setup.tableWidget->item(i, 0);
			//QTableWidgetItem* pItem1 = m_setup.tableWidget->item(i, 1);
			QTableWidgetItem* pItem2 = m_setup.tableWidget->item(i, 2);
			
			if (pItem0->text().size() != 0)
			{
				QString strValue = strFormat.arg(pItem0->text()).arg(pItem2->text());
				colorTable.setValue("COLOR_MAP/pair" + QString("%1").arg(iSure++), strValue);
			}
			
		}

		colorTable.setValue("VALUE_COUNT/count", iSure - 1);

		QFileInfo fi(fileName);
		fileList.setValue("DEFALUTDIR/color_table_dir", fi.absolutePath());
	}

	this->close();
}

void ColorTableDialog::slot_open(bool)
{
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/color_table_dir").toString();

	QString file = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开颜色表"), strDefalutOpenDir, "*.ini");

	if (file.size() != 0)
	{
		QSettings configIniWrite(file, QSettings::IniFormat);
		int iCount = configIniWrite.value("VALUE_COUNT/count").toInt();
		int iType = configIniWrite.value("TYPE/section").toInt();

		for (int i = 0; i < iCount; i++)
		{
			QString strPath = "COLOR_MAP/pair" + QString("%1").arg(i + 1);
			QString strPair = configIniWrite.value(strPath).toString();
			QStringList strList = strPair.split(':');
			if (strList.length() > 1)
			{
				float fkey = strList[0].toFloat();
				QStringList strColor = strList[1].split(",");

				int iR(0), iG(0), iB(0);

				if (strColor.length() > 2)
				{
					iR = strColor[0].toInt();
					iG = strColor[1].toInt();
					iB = strColor[2].toInt();
				}

				int iIndex = m_setup.tableWidget->rowCount();
				m_setup.tableWidget->insertRow(iIndex);

				QTableWidgetItem* pValueItem = new QTableWidgetItem();
				pValueItem->setText(QString("%1").arg(fkey));
				m_setup.tableWidget->setItem(iIndex, 0, pValueItem);

				QTableWidgetItem* pColorItem = new QTableWidgetItem();
				pColorItem->setBackground(QColor(iR, iG, iB));
				m_setup.tableWidget->setItem(iIndex, 1, pColorItem);

				QTableWidgetItem* pColorValueItem = new QTableWidgetItem();
				pColorValueItem->setText(QString("%1, %2, %3").arg(iR).arg(iG).arg(iB));
				m_setup.tableWidget->setItem(iIndex, 2, pColorValueItem);
			}
		}

		if (iType) m_setup.NoLinerCheckBox->setChecked(true);
	}
}

void ColorTableDialog::slot_cellDoubleClicked(int row, int column)
{
	if (column == 1)
	{
		QTableWidgetItem* pItem = m_setup.tableWidget->item(row, column);
		QColor bc = pItem->backgroundColor();
		QColor newBc = bc;
		QColorDialog cd(bc, this);
		int iR = cd.exec();

		if (iR == QDialog::Accepted)
		{
			newBc = cd.currentColor();
		}
		
		pItem->setBackground(newBc);
		QTableWidgetItem* pItem2 = m_setup.tableWidget->item(row, 2);
		pItem2->setText(QString("%1, %2, %3").arg(newBc.red()).arg(newBc.green()).arg(newBc.blue()));
	}
}

void ColorTableDialog::slot_cellClicked(int row, int column)
{
	/*switch (column)
	{
	case 0:
		break;
	case 1:
	{
		QTableWidgetItem* pItem = m_setup.tableWidget->item(row, column);
		QColor bc = pItem->backgroundColor();
		QColor newBc = QColorDialog::getColor(bc);
		pItem->setBackground(newBc);

		QTableWidgetItem* pItem2 = m_setup.tableWidget->item(row, 2);
		pItem2->setText(QString("%1, %2, %3").arg(newBc.red()).arg(newBc.green()).arg(newBc.blue()));
		
	}
		break;
	case 2:
		break;
	default:
		break;
	}*/
}

void ColorTableDialog::slot_cellChanged(int row, int column)
{
	if (column == 2)
	{
		QTableWidgetItem* pItem2 = m_setup.tableWidget->item(row, 2);
		QString strColor = pItem2->text();
		QStringList strRGB = strColor.split(",");
		if (strRGB.size() < 3) return;
		int iR, iG, iB;
		iR = strRGB[0].toInt();
		iG = strRGB[1].toInt();
		iB = strRGB[2].toInt();

		QTableWidgetItem* pItem = m_setup.tableWidget->item(row, 1);
		pItem->setBackground(QColor(iR, iG, iB));
	}
}