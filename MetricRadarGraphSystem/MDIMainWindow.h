#pragma once
#include "ui_MainWindowUI.h"

class ColorBar;

class MDIMainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	MDIMainWindow();
	~MDIMainWindow();
	void LoadConfigure(const QString& colorTableFile);
	QWidget* OpenRasterFile(const QString& fileName);
	QWidget* OpenCurveFile(const QString & filename);
	void OpenMainConfig(const QString& fileName);
	int OpenFile(const QString& fileName, QWidget** subWin = 0);
	int DisplayDirFile(const QString& cfgFile, const QString& strDir);
	QMdiSubWindow* GetMySubWindow(const QString& strFilePathName);
	void SaveToImageFile(QwtPlot* pPlot, const QString& strFile);
	int RunAlgorithm1(const float* InputPoints, size_t inputLen, float** outputPoints, size_t* outputLen, const char* funName);
	void SaveFile(const QString & strFile, QMdiSubWindow* pSubwin);

public slots:
	void slot_openFile(bool);
	void slot_openDir(bool);
	void slot_doubleClicked(const QModelIndex &index);
	void slot_save(bool);
	void slot_saveall(bool);
	void slot_mainSettings(bool);
	void slot_createColorTable(bool);
	void slot_legendDataChanged(const QVariant &itemInfo,
		const QList<QwtLegendData> &data);
	void slot_TileWindows(bool);
	void slot_CascadeWindows(bool);
	//void slot_CurrentPoint(const QPointF& pos);
	void slot_CloseDir(bool);
	void slot_Exit(bool);
	void slot_CloseAllWinAction(bool);

	void slot_subWindowActivated(QMdiSubWindow *window);

private:
	QWidget* MakeNewWidget(QWidget* leftWidget, const QString& strFile, const QString& strFileType = "");
	Ui::MainWindow m_setupUI;
	
	QString m_raster_extends;
	QString m_curve_extends;
	QMap<QString, QwtSymbol::Style> m_symbol_map;
	QMap<QString, QString> m_FileSaveFormat;
	QMap<QString, QString> m_RightAxisNames;
	QMap<QString, QString> m_expression;
	QMap<QString, QMap<QString, QString>> m_uiParameter;
	QMap<QString, int> m_deleteMinLabel;
	QStringList m_classify_name;
	QStringList m_classify_extend;
	int m_classify_count;
	QMdiSubWindow* m_pCurrentWindow;
	QStandardItemModel* m_pStandardItemModel = new QStandardItemModel();
	QMdiArea* mdiArea = new QMdiArea;
	void TraverseTreeAndClose(QStandardItem* pTreeNode);
};

