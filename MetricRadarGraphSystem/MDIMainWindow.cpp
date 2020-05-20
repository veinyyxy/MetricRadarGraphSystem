#include "stdafx.h"
#include "MDIMainWindow.h"
#include "RasterPlot.h"
#include "RadarRasterData.h"
#include "ParseRasterFile.h"
#include "RadarColorMap.h"
#include "ConfigurableColorBar.h"
#include "AccessClassifyConfig.h"
#include "RadarCurveData.h"
#include "ColorTableDialog.h"
#include "TableView.h"
#include "MyLegend.h"
#include "NonlinearityColorBarWidget.h"
#include "SubWindow.h"
#include "MainSettingsDialog.h"
#include "TimeScaleDraw.h"

MDIMainWindow::MDIMainWindow() : m_pCurrentWindow(0)
{
	
	m_setupUI.setupUi(this);
	this->setCentralWidget(mdiArea);
	//m_setupUI.treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_setupUI.toolBar->setWindowTitle(QString::fromLocal8Bit("工具栏"));
	m_setupUI.dockWidget->setWindowTitle(QString::fromLocal8Bit("文件树"));
	m_setupUI.dockWidgetContents->resize(QSize(600, 2000));
	//QRect rect = m_setupUI.dockWidget->geometry();
	//m_setupUI.dockWidget->setGeometry(QRect(rect.x(), rect.y(), 600, rect.height()));
	m_setupUI.dockWidget->setMinimumWidth(260);
	m_setupUI.dockWidget->showMinimized();

	m_setupUI.MainSettings->setVisible(false);
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	this->setWindowIcon(QIcon("./icon/app.png"));

	m_setupUI.treeView->header()->hide();
	m_setupUI.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_setupUI.OpenFile->setIcon(QIcon("./icon/openfiles.png"));
	m_setupUI.OpenDir->setIcon(QIcon("./icon/opendir.png"));
	m_setupUI.ColorTable->setIcon(QIcon("./icon/colortable.png"));
	m_setupUI.Export->setIcon(QIcon("./icon/export.png"));
	m_setupUI.ExportAll->setIcon(QIcon("./icon/exportAll.png"));
	m_setupUI.CloseDirAction->setIcon(QIcon("./icon/classAll.png"));
	m_setupUI.MainSettings->setIcon(QIcon("./icon/MainSettings.png"));
	m_setupUI.CloseAllWinAction->setIcon(QIcon("./icon/closeWins.png"));

	m_setupUI.toolBar->addAction(m_setupUI.OpenFile);
	m_setupUI.toolBar->addAction(m_setupUI.OpenDir);
	//m_setupUI.toolBar->addAction(m_setupUI.CurrentFile);
	m_setupUI.toolBar->addAction(m_setupUI.Export);
	m_setupUI.toolBar->addAction(m_setupUI.ExportAll);
	m_setupUI.toolBar->addSeparator();
	m_setupUI.toolBar->addAction(m_setupUI.ColorTable);
	//m_setupUI.toolBar->addAction(m_setupUI.MainSettings);
	m_setupUI.toolBar->addSeparator();
	m_setupUI.toolBar->addAction(m_setupUI.CloseDirAction);
	m_setupUI.toolBar->addAction(m_setupUI.CloseAllWinAction);

	connect(m_setupUI.OpenFile, SIGNAL(triggered(bool)), this, SLOT(slot_openFile(bool)));
	connect(m_setupUI.OpenDir, SIGNAL(triggered(bool)), this, SLOT(slot_openDir(bool)));
	connect(m_setupUI.Export, SIGNAL(triggered(bool)), this, SLOT(slot_save(bool)));
	connect(m_setupUI.ExportAll, SIGNAL(triggered(bool)), this, SLOT(slot_saveall(bool)));
	connect(m_setupUI.ColorTable, SIGNAL(triggered(bool)), this, SLOT(slot_createColorTable(bool)));
	connect(m_setupUI.MainSettings, SIGNAL(triggered(bool)), this, SLOT(slot_mainSettings(bool)));
	connect(m_setupUI.TileWindowsAction, SIGNAL(triggered(bool)), this, SLOT(slot_TileWindows(bool)));
	connect(m_setupUI.CascadeWindowsAction, SIGNAL(triggered(bool)), this, SLOT(slot_CascadeWindows(bool)));
	connect(m_setupUI.CloseDirAction, SIGNAL(triggered(bool)), this, SLOT(slot_CloseDir(bool)));
	connect(m_setupUI.CloseAllWinAction, SIGNAL(triggered(bool)), this, SLOT(slot_CloseAllWinAction(bool)));
	connect(m_setupUI.Exit, SIGNAL(triggered(bool)), this, SLOT(slot_Exit(bool)));

	connect(m_setupUI.treeView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slot_doubleClicked(const QModelIndex &)));
	//connect(m_setupUI.mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), SLOT(slot_subWindowActivated(QMdiSubWindow *)));
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), SLOT(slot_subWindowActivated(QMdiSubWindow *)));
}


MDIMainWindow::~MDIMainWindow()
{
	
}


void MDIMainWindow::LoadConfigure(const QString& colorTableFile)
{
	
}

QWidget* MDIMainWindow::OpenRasterFile(const QString& fileName)
{
	QSettings cfg("./FileClassify.ini", QSettings::IniFormat);
	QFileInfo fi(fileName);
	QString suffixName = fi.suffix();
	QString strKey = QString::fromLocal8Bit("TITLE/") + suffixName;
	QString strTitle = QString(cfg.value(strKey).toString().toLatin1());
	strKey = "COLORTABLE/" + suffixName;
	QString colorTableFile = cfg.value(strKey).toString();

	if (colorTableFile.size() == 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("无法打开文件"), QString::fromLocal8Bit("无法打开文件，颜色表无法找到。"));
		return 0;
	}

	QMap<QString, QString> KeyValues = m_uiParameter.value(suffixName);
	QString strFontName = KeyValues.value("FontName");
	QFont globleFont(strFontName);

	RadarColorMap* RCM = new RadarColorMap;
	ConfigurableColorBar ccb;
	ccb.LoadData(colorTableFile.toStdString());
	QString strRightName = m_RightAxisNames.value(suffixName);

	if (ccb.GetBarStyle() == ColorBar::LINEAR)
	{
		RasterPlot* plot = new RasterPlot();
		plot->setFont(globleFont);
		plot->canvas()->setFont(globleFont);
		QwtColorMap* pLinearColorMap = RCM->Make(&ccb);
		QwtColorMap* pLinearColorMap2 = RCM->Make(&ccb);
		RadarRasterData* pRRD = new RadarRasterData();
		pRRD->SetFillValue(RCM->GetMin() + RCM->GetSetp() / 2);
		pRRD->SetMaxValue(RCM->GetMax());

		ParseRasterFile rrf;
		rrf.m_strExpression = m_expression.value(suffixName);
		rrf.ReadDataFromFile(fileName.toStdString());
		rrf.SetAxisProperty(0, 150, 0, 15, RCM->GetMin(), RCM->GetMax());
		//plot->SetStationName(rrf.m_strStationName);
		plot->SetValueSetp(RCM->GetSetp());
		pRRD->Make(&rrf);

		int isHideLable = m_deleteMinLabel.value(suffixName);
		if (isHideLable > 0)
		{
			plot->SetHideLable(RCM->GetMin());
		}
		
		std::string strXComment;
		std::string strYComment;
		std::string strZComment;
		rrf.GetAxisComment(strXComment, strYComment, strZComment);

		QDateTime dt = QDateTime::fromString(QString::fromStdString(strXComment), "yyyyMMddhhmmsszzz");
		QwtText topTitle, leftTitle, rightTitle, bottomTitle;
		topTitle.setText(strTitle); topTitle.setFont(globleFont);
		leftTitle.setText(QString::fromStdString(strYComment)); leftTitle.setFont(globleFont);
		rightTitle.setText(strRightName); rightTitle.setFont(globleFont);
		bottomTitle.setText(QString::fromLocal8Bit("NAQU-") + dt.date().toString("yyyyMMdd")); bottomTitle.setFont(globleFont);
		
		plot->setTitle(strTitle);
		plot->SetStartDateTime(dt);

		plot->setAxisTitle(QwtPlot::xBottom, bottomTitle);
		plot->setAxisTitle(QwtPlot::yLeft, leftTitle);
		plot->setAxisTitle(QwtPlot::yRight, rightTitle);

		plot->SetColorMap(pLinearColorMap);
		plot->SetAxisColorMap(pLinearColorMap2);
		plot->SetRasterData(pRRD);

		plot->DrawPlot();

		return plot;
	}
	else
	{
		RasterPlot* plot = new RasterPlot();
		plot->setFont(globleFont);
		plot->canvas()->setFont(globleFont);

		QwtColorMap* pLinearColorMap = RCM->Make(&ccb);
		QwtColorMap* pLinearColorMap2 = RCM->Make(&ccb);
		RadarRasterData* pRRD = new RadarRasterData();
		pRRD->SetFillValue(RCM->GetMin() - 3);
		pRRD->SetMaxValue(RCM->GetMax());

		ParseRasterFile rrf;
		rrf.m_strExpression = m_expression.value(suffixName);
		rrf.ReadDataFromFile(fileName.toStdString());
		rrf.SetAxisProperty(0, 150, 0, 15, RCM->GetMin(), RCM->GetMax());
		//plot->SetStationName(rrf.m_strStationName);
		plot->SetValueSetp(RCM->GetSetp());
		pRRD->Make(&rrf);

		std::string strXComment;
		std::string strYComment;
		std::string strZComment;
		rrf.GetAxisComment(strXComment, strYComment, strZComment);
		
		QDateTime dt = QDateTime::fromString(QString::fromStdString(strXComment), "yyyyMMddhhmmsszzz");
		QwtText topTitle, leftTitle, rightTitle, bottomTitle;
		topTitle.setText(strTitle); topTitle.setFont(globleFont);
		leftTitle.setText(QString::fromStdString(strYComment)); leftTitle.setFont(globleFont);
		rightTitle.setText(strRightName); rightTitle.setFont(globleFont);
		bottomTitle.setText(QString::fromLocal8Bit("NAQU-") + dt.date().toString("yyyyMMdd")); bottomTitle.setFont(globleFont);

		plot->setTitle(strTitle);
		plot->SetStartDateTime(dt);
		
		plot->setAxisTitle(QwtPlot::xBottom, bottomTitle);
		plot->setAxisTitle(QwtPlot::yLeft, leftTitle);
		plot->setAxisTitle(QwtPlot::yRight, rightTitle);

		plot->SetColorMap(pLinearColorMap);
		plot->SetAxisColorMap(pLinearColorMap2);
		plot->SetRasterData(pRRD);

		plot->DrawPlot();
		plot->enableAxis(QwtPlot::yRight, false);

		QWidget* newWidget = MakeNewWidget(plot, colorTableFile, suffixName);

		return newWidget;
	}
}

QWidget* MDIMainWindow::OpenCurveFile(const QString& filename)
{
	QPointer<TableView> pTV = new TableView();

	RadarCurveData rcd;
	rcd.ReadDataFromFile(filename.toStdString());
	//QString strTime = QString("%1%2%3").arg(rcd.fh.inthours).arg(rcd.fh.intminutes).arg(rcd.fh.intseconds);
	QTime startTime;
	startTime.setHMS(rcd.fh.inthours, rcd.fh.intminutes, rcd.fh.intseconds);
	QDate startDate;
	startDate.setDate(rcd.fh.intyears, rcd.fh.intmonths, rcd.fh.intdays);

	BasicPlot* plot = new BasicPlot();
	//plot->setPalette(QPalette(Qt::transparent));
	//plot->setFont(QFont("Times New Roman"));
	plot->setAutoFillBackground(true);

	/*connect(plot, SIGNAL(legendDataChanged(const QVariant&,
		const QList<QwtLegendData>&)), this, SLOT(slot_legendDataChanged(const QVariant&,
			const QList<QwtLegendData>&)));*/
	QSettings cfg("FileClassify.ini", QSettings::IniFormat);
	//QString strNames = QString(cfg.value("TYPE/classify_name").toString().toLatin1());
	//QString tempText = QString(cfg.value("TITLE/ParaBB").toString().toLatin1());
	QFileInfo fi(filename);
	QString strSuffix = fi.suffix();
	//QByteArray buff = cfg.value("TITLE/" + strSuffix).toByteArray();
	QString strTitles = QString(cfg.value("TITLE/" + strSuffix).toString().toLatin1());// QString::fromUtf8(buff.data());
	//QString strTitles = cfg.value("TITLE/" + strSuffix).toString();
	QStringList strTitleList = strTitles.split("|");
	
	QMap<QString, QString> KeyValues = m_uiParameter.value(strSuffix);
	QString strFontName = KeyValues.value("FontName");
	QFont globleFont(strFontName);
	QwtText topTitle, leftTitle, bottomTitle;
	topTitle.setText(strTitleList.at(0)); topTitle.setFont(globleFont);
	leftTitle.setText("Height(km)"); leftTitle.setFont(globleFont);
	bottomTitle.setText(startDate.toString("yyyyMMdd") + QString::fromLocal8Bit(rcd.fh.radar_name)+"Time/BJT"); bottomTitle.setFont(globleFont);

	plot->setFont(globleFont);
	if(strTitleList.size() > 1)
	{
		plot->setTitle(strTitleList.at(0));
	}

	TimeScaleDraw* timeScaleDraw = new TimeScaleDraw(startTime);
	QwtDateScaleEngine *scaleEngine = new QwtDateScaleEngine(Qt::UTC);

	plot->setAxisScaleDraw(QwtPlot::xBottom, timeScaleDraw);
	plot->setAxisScaleEngine(QwtPlot::xBottom, scaleEngine);
	plot->setAxisTitle(QwtPlot::xBottom, bottomTitle);
	plot->setAxisTitle(QwtPlot::yLeft, leftTitle);

	/*plot->setBackgroundRole(QPalette::Background);
	plot->setCanvasBackground(Qt::black);*/
	plot->setAxisScale(QwtPlot::yLeft, 0.0, 15.0, 3.000);
	plot->setAxisScale(QwtPlot::xBottom, 0.0, 500.0);

	//plot->insertLegend(new QwtLegend());
	//QwtPlotShapeItem* pItem = new QwtPlotShapeItem();
	MyLegend* pLegend = new MyLegend();
	
	plot->insertLegend(pLegend);

	//QwtPlotLegendItem* pLegend = new QwtPlotLegendItem();
	//pLegend->attach(plot);

	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setFont(globleFont);
	//canvas->setFrameStyle(QFrame::Box);
	//canvas->setLineWidth(1);
	
	QPalette canvasPalette(Qt::white);
	canvasPalette.setColor(QPalette::Foreground, QColor(255, 255, 255));
	canvas->setPalette(canvasPalette);

	canvas->setBorderRadius(10);
	plot->setCanvas(canvas);
	
	QwtPlotZoomer* zoomer = new QwtPlotZoomer(canvas);
	zoomer->setRubberBandPen(QColor(Qt::black));
	zoomer->setTrackerPen(QColor(Qt::black));
	zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
		Qt::RightButton, Qt::ControlModifier);
	zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
		Qt::RightButton);

	QwtPlotPanner *panner = new QwtPlotPanner(canvas);
	panner->setMouseButton(Qt::MidButton);

	/*QwtPlotGrid *grid = new QwtPlotGrid();
	grid->setPen(Qt::red, 1, Qt::PenStyle::DashDotDotLine);
	grid->attach(plot);*/
	///////////////////////////////////////云底数据////////////////////////////////////////////////////
	{
		// LeftButton for the zooming
		// MidButton for the panning
		// RightButton: zoom out by 1
		// Ctrl+RighButton: zoom out to full size

		/*QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse,
			QBrush(Qt::yellow), QPen(Qt::red, 2), QSize(8, 8));
		curve->setSymbol(symbol);*/
		
#if 1
		for (int l = 0; l < 1; l++)
		{
			float pCurrentV = -32768.0;
			QPolygonF CloundbasePoints;
			for (int i = 0; i < rcd.fh.Num_beam; i++)
			{
				float pV = rcd.dt.Hcloudbase[l * 10 + i] / 1000;
				if (i == 0) pCurrentV = pV;
				if (abs(pV - (-32768)) < 0.0001)
				{
					continue;
				}
				else
				{
					if (abs(pCurrentV - pV) > 1.000)
					{
						if (CloundbasePoints.size())
						{
							QwtPlotCurve *CloundbaseCurve = new QwtPlotCurve();

							CloundbaseCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
							//CloundbaseCurve->setTitle("Some Points");
							CloundbaseCurve->setPen(Qt::red, 2, Qt::DashDotDotLine),
								CloundbaseCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
							CloundbaseCurve->setSamples(CloundbasePoints);
							CloundbaseCurve->attach(plot);

							CloundbasePoints.clear();
							CloundbasePoints.push_back(QPointF(i, pV));
							pCurrentV = pV;
						}
						continue;
					}
					else
					{
						CloundbasePoints.push_back(QPointF(i, pV));
						pCurrentV = pV;
					}
				}
			}

			if (CloundbasePoints.size())
			{
				QwtPlotCurve *CloundbaseCurve = new QwtPlotCurve();
				CloundbaseCurve->setTitle("Base");
				CloundbaseCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
				//CloundbaseCurve->setTitle("Some Points");
				CloundbaseCurve->setPen(Qt::red, 2, Qt::DashDotDotLine),
					CloundbaseCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
				CloundbaseCurve->setSamples(CloundbasePoints);
				CloundbaseCurve->attach(plot);
			}
		}
		
#else
		float* outBuffer = 0;
		size_t outSize = 0;
		int iRunResult = RunAlgorithm1(rcd.dt.Hcloudbase, rcd.fh.Num_beam * 10, &outBuffer, &outSize, "run_CloundBase_algorithm");

		if (outSize == 0 && iRunResult)
		{
			for (int i = 0; i < rcd.fh.Num_beam * 10; i++)
			{
				float pV = rcd.dt.Hcloudbase[i] / 1000;
				CloundbasePoints.push_back(QPointF(i, pV));
			}
		}
		else
		{
			for (int i = 0; i < outSize; i++)
			{
				float pV = outBuffer[i] / 1000;
				CloundbasePoints.push_back(QPointF(i, pV));
			}

			delete[] outBuffer;
		}
		
#endif
	}
	/////////////////////////////////////////////云顶数据///////////////////////////////////////////
	{
		QPolygonF CloundtopPoints;
#if 1
		for (int l = 0; l < 1; l++)
		{
			float pCurrentV = -32768.0;
			QPolygonF CloundbasePoints;
			for (int i = 0; i < rcd.fh.Num_beam; i++)
			{
				float pV = rcd.dt.Hcloudtop[l * 10 + i] / 1000;
				if (i == 0) pCurrentV = pV;
				if (abs(pV - (-32768)) < 0.0001)
				{
					continue;
				}
				else
				{
					if (abs(pCurrentV - pV) > 1.000)
					{
						if (CloundtopPoints.size())
						{
							QwtPlotCurve *CloundtopCurve = new QwtPlotCurve();
							//CloundtopCurve->setTitle("Top");
							CloundtopCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
							//CloundbaseCurve->setTitle("Some Points");
							CloundtopCurve->setPen(Qt::blue, 2, Qt::SolidLine),
								CloundtopCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
							CloundtopCurve->setSamples(CloundtopPoints);
							CloundtopCurve->attach(plot);

							CloundtopPoints.clear();
							CloundtopPoints.push_back(QPointF(i, pV));
							pCurrentV = pV;
						}
						continue;
					}
					else
					{
						CloundtopPoints.push_back(QPointF(i, pV));
						pCurrentV = pV;
				}
			}
		}

		if (CloundtopPoints.size())
		{
			QwtPlotCurve *CloundtopCurve = new QwtPlotCurve();
			CloundtopCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
			CloundtopCurve->setTitle("Top");
			CloundtopCurve->setPen(Qt::blue, 2, Qt::SolidLine),
				CloundtopCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
			CloundtopCurve->setSamples(CloundtopPoints);
			CloundtopCurve->attach(plot);
		}
	}
#else
		float* outBuffer = 0;
		size_t outSize = 0;
		int iRunResult = RunAlgorithm1(rcd.dt.Hcloudtop, rcd.fh.Num_beam * 10, &outBuffer, &outSize, "run_CloundTop_algorithm");

		if (outSize == 0 && iRunResult)
		{
			for (int i = 0; i < rcd.fh.Num_beam * 10; i++)
			{
				float pV = rcd.dt.Hcloudtop[i] / 1000;
				CloundtopPoints.push_back(QPointF(i, pV));
			}
		}
		else
		{
			for (int i = 0; i < outSize; i++)
			{
				float pV = outBuffer[i] / 1000;
				CloundtopPoints.push_back(QPointF(i, pV));
			}

			delete[] outBuffer;
		}
#endif
	}
	///////////////////////////////////////////////云分类数据///////////////////////////////////////////
#if 1
	QSet<QString> title;
	{//顶高云分类
		QMap<QString, QwtPlotCurve*> Curves;
		QMap<QString, QwtSymbol*> Symbols;
		QMap<QString, QPolygonF> Samples;

		for (int i = 0; i < rcd.fh.Num_beam; i+=25)
		{
			float pV = rcd.dt.Hcloudtop[i] / 1000;
			if (pV - (-32768) < 0.0001)
			{
				continue;
			}

			char* pType = rcd.dt.Classcloud + 0 * rcd.fh.Num_beam + i * 2;

			char pText[3] = { 0 };
			memcpy_s(pText, 3, pType, 2);

			QString strKey(pText);
			QwtSymbol::Style vS = m_symbol_map.value(strKey, QwtSymbol::NoSymbol);
			if (vS == QwtSymbol::NoSymbol)
				continue;
			QwtSymbol *symbol = Symbols.value(strKey);
			QwtPlotCurve* pClasscloudCurve = Curves.value(strKey);
			
			if (pClasscloudCurve == nullptr)
			{
				pClasscloudCurve = new QwtPlotCurve();
				pClasscloudCurve->setStyle(QwtPlotCurve::NoCurve);
				Curves.insert(strKey, pClasscloudCurve);
			}
			

			if (symbol == nullptr)
			{
				
				QwtSymbol *symbol = new QwtSymbol(vS,
					QBrush(Qt::yellow), QPen(Qt::red, 1), QSize(8, 8));
				
				pClasscloudCurve->setSymbol(symbol);
				pClasscloudCurve->attach(plot);

				Symbols.insert(strKey, symbol);
				
			}
			else
			{
				
			}

			QPolygonF ClasscloudPoints = Samples.value(strKey);
			if (ClasscloudPoints.size() == 0)
			{
				QPolygonF temp;
				temp.push_back(QPointF(i, pV));
				Samples.insert(strKey, temp);
			}
			else
			{
				ClasscloudPoints.push_back(QPointF(i, pV));
				Samples.insert(strKey, ClasscloudPoints);
			}
		}

		QList<QString> strKeyList = Curves.keys();
		for (int i = 0; i < strKeyList.size(); ++i)
		{
			QString strKey = strKeyList.at(i);

			QwtPlotCurve* pCurve = Curves.value(strKey);
			pCurve->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);
			
			QPolygonF ClasscloudPoints = Samples.value(strKey);
			QSet<QString>::iterator finded = title.find(strKey);
			if (finded == title.end())
			{
				pCurve->setTitle(strKey);
				title.insert(strKey);
			}
			pCurve->setSamples(ClasscloudPoints);
			pCurve->attach(plot);
		}
		/////////////////////////////////////////////////////////////////////////
		
	}
	
	{//底高云分类
		QMap<QString, QwtPlotCurve*> Curves;
		QMap<QString, QwtSymbol*> Symbols;
		QMap<QString, QPolygonF> Samples;

		for (int i = 0; i < rcd.fh.Num_beam; i += 25)
		{
			float pV = rcd.dt.Hcloudbase[i] / 1000;
			if (pV - (-32768) < 0.0001)
			{
				continue;
			}

			char* pType = rcd.dt.Classcloud + 0 * rcd.fh.Num_beam + i * 2;

			char pText[3] = { 0 };
			memcpy_s(pText, 3, pType, 2);

			QString strKey(pText);
			QwtSymbol::Style vS = m_symbol_map.value(strKey, QwtSymbol::NoSymbol);

			if (vS == QwtSymbol::NoSymbol)
				continue;

			QwtSymbol *symbol = Symbols.value(strKey);
			QwtPlotCurve* pClasscloudCurve = Curves.value(strKey);
			if (pClasscloudCurve == nullptr)
			{
				pClasscloudCurve = new QwtPlotCurve();
				pClasscloudCurve->setStyle(QwtPlotCurve::NoCurve);
				Curves.insert(strKey, pClasscloudCurve);
			}


			if (symbol == nullptr)
			{

				QwtSymbol *symbol = new QwtSymbol(vS,
					QBrush(Qt::yellow), QPen(Qt::red, 1), QSize(8, 8));

				pClasscloudCurve->setSymbol(symbol);
				pClasscloudCurve->attach(plot);

				Symbols.insert(strKey, symbol);

			}
			else
			{

			}

			QPolygonF ClasscloudPoints = Samples.value(strKey);
			if (ClasscloudPoints.size() == 0)
			{
				QPolygonF temp;
				temp.push_back(QPointF(i, pV));
				Samples.insert(strKey, temp);
			}
			else
			{
				ClasscloudPoints.push_back(QPointF(i, pV));
				Samples.insert(strKey, ClasscloudPoints);
			}
		}

		QList<QString> strKeyList = Curves.keys();
		
		for (int i = 0; i < strKeyList.size(); ++i)
		{
			QString strKey = strKeyList.at(i);

			QwtPlotCurve* pCurve = Curves.value(strKey);
			pCurve->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);
			QSet<QString>::iterator finded = title.find(strKey);
			if (finded == title.end())
			{
				pCurve->setTitle(strKey);
				title.insert(strKey);
			}
			QPolygonF ClasscloudPoints = Samples.value(strKey);
			pCurve->setSamples(ClasscloudPoints);
			pCurve->attach(plot);
		}
		/////////////////////////////////////////////////////////////////////////

	}

#endif
	QString strTabName = QString::fromLocal8Bit("云底、云顶");
	if (strTitleList.size() > 1)
		strTabName = strTitleList.at(0);
	pTV->AddTable(plot, strTabName);

	{//亮带图
		BasicPlot* plot1 = new BasicPlot();
		plot1->setAutoFillBackground(true);
		plot1->setFont(globleFont);

		if (strTitleList.size() > 1)
		{
			QwtText titleText(strTitleList.at(1));
			titleText.setFont(globleFont);
			plot1->setTitle(strTitleList.at(1));
		}
			

		QwtPlotGrid *grid = new QwtPlotGrid();
		grid->setPen(Qt::red, 1, Qt::DotLine);
		grid->attach(plot1);

		plot1->setCanvasBackground(Qt::white);


		TimeScaleDraw* timeScaleDraw = new TimeScaleDraw(startTime);
		QwtDateScaleEngine *scaleEngine = new QwtDateScaleEngine(Qt::UTC);

		plot1->setAxisScaleDraw(QwtPlot::xBottom, timeScaleDraw);
		plot1->setAxisScaleEngine(QwtPlot::xBottom, scaleEngine);
		plot1->setAxisTitle(QwtPlot::xBottom, bottomTitle);
		plot1->setAxisTitle(QwtPlot::yLeft, leftTitle);

		plot1->setAxisScale(QwtPlot::yLeft, 0.0, 15.0, 3.000);
		plot1->setAxisScale(QwtPlot::xBottom, 0.0, 500.0);
		QwtLegend* pLegend = new QwtLegend();
		
		plot1->insertLegend(pLegend);


		QwtPlotCanvas *canvas = new QwtPlotCanvas();
		QPalette canvasPalette(Qt::white);
		canvasPalette.setColor(QPalette::Foreground, QColor(255, 255, 255));
		canvas->setPalette(canvasPalette);
		canvas->setFont(globleFont);

		canvas->setBorderRadius(10);
		plot1->setCanvas(canvas);

		QwtPlotZoomer* zoomer = new QwtPlotZoomer(canvas);
		zoomer->setRubberBandPen(QColor(Qt::black));
		zoomer->setTrackerPen(QColor(Qt::black));
		zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
			Qt::RightButton, Qt::ControlModifier);
		zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
			Qt::RightButton);

		QwtPlotPanner *panner = new QwtPlotPanner(canvas);
		panner->setMouseButton(Qt::MidButton);

		QPolygonF CloundbasePoints;
		QPolygonF CloundtopPoints;
		QPolygonF CloundmidPoints;
		for (int i = 0; i < rcd.fh.Num_beam; i++)
		{
			float pmid = rcd.dt.Hbbmid[i];
			if (!(abs(pmid - (-32768)) < 0.0001))
			{
				CloundmidPoints.append(QPointF(i, pmid / 1000.0));
			}
			
			float pbase = rcd.dt.Hbblow[i];
			if (!(abs(pbase - (-32768)) < 0.0001))
			{
				CloundbasePoints.append(QPointF(i, pbase / 1000.0));
			}
			
			float ptop = rcd.dt.Hbbup[i];
			if (!(abs(pmid - (-32768)) < 0.0001))
			{
				CloundtopPoints.append(QPointF(i, ptop / 1000.0));
			}
		}

		if (CloundmidPoints.size() == 0 && CloundbasePoints.size() == 0 && CloundtopPoints.size() == 0)
		{
			return pTV;
		}

		{
			QwtPlotCurve *CloundbaseCurve = new QwtPlotCurve();
			CloundbaseCurve->setTitle("Top");
			CloundbaseCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
			CloundbaseCurve->setPen(Qt::green, 1, Qt::DashLine),
				CloundbaseCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
			CloundbaseCurve->setSamples(CloundtopPoints);
			CloundbaseCurve->attach(plot1);
		}

		{
			QwtPlotCurve *CloundbaseCurve = new QwtPlotCurve();
			CloundbaseCurve->setTitle("Mid");
			CloundbaseCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
			CloundbaseCurve->setPen(Qt::green, 3, Qt::SolidLine),
				CloundbaseCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
			CloundbaseCurve->setSamples(CloundmidPoints);
			CloundbaseCurve->attach(plot1);
		}

		{
			QwtPlotCurve *CloundbaseCurve = new QwtPlotCurve();
			CloundbaseCurve->setTitle("Base");
			CloundbaseCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
			CloundbaseCurve->setPen(Qt::green, 1, Qt::DotLine),
				CloundbaseCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
			CloundbaseCurve->setSamples(CloundbasePoints);
			CloundbaseCurve->attach(plot1);
		}

		QString strTabName = QString::fromLocal8Bit("亮带识别");
		if (strTitleList.size() > 1)
			strTabName = strTitleList.at(1);

		pTV->AddTable(plot1, strTabName);
	}

	return pTV;
}

void MDIMainWindow::OpenMainConfig(const QString & fileName)
{
	//QStringList headerList;
	//headerList.push_back(QString::fromLocal8Bit("状态"));
	//headerList.push_back(QString::fromLocal8Bit("文件名"));

	//pStandardItemModel->setColumnCount(4);
	//pStandardItemModel->setHorizontalHeaderLabels(headerList);
	
	AccessClassifyConfig::ClassifyConfig classifyConfig;
	AccessClassifyConfig acc;
	acc.ReadConfig(fileName, &classifyConfig);

	m_raster_extends = classifyConfig.raster_extends;
	m_curve_extends = classifyConfig.curve_extends;
	m_FileSaveFormat = classifyConfig.saveFileFormat;
	m_RightAxisNames = classifyConfig.rightAxisNames;
	m_expression = classifyConfig.expression;
	m_uiParameter = classifyConfig.uiParameter;
	m_symbol_map = classifyConfig.symbol_map;
	m_classify_name = classifyConfig.classify_name;
	m_classify_count = classifyConfig.classify_count;
	m_classify_extend = classifyConfig.classify_extend;
	m_deleteMinLabel = classifyConfig.deleteMinLabel;
	m_setupUI.treeView->setModel(m_pStandardItemModel);
}

int MDIMainWindow::OpenFile(const QString & fileName, QWidget** subWin)
{
	QWidget* pSubWidget = 0;
	QFileInfo fileInfo(fileName);
	QString strSuffix = fileInfo.suffix();
	QString strFileFullName = fileInfo.fileName();
	QIcon subWinIcon;
	if (m_raster_extends.indexOf(strSuffix) >= 0)
	{
		pSubWidget = OpenRasterFile(fileName);
		subWinIcon.addFile("./icon/raster.png");
	}
	else if (m_curve_extends.indexOf(strSuffix) >= 0)
	{
		pSubWidget = OpenCurveFile(fileName);
		subWinIcon.addFile("./icon/curve.png");
	}
	else
	{
		return 0;
	}

	if (pSubWidget == 0)
	{
		return 0;
	}
		
	//QMdiSubWindow* newSubWin = m_setupUI.mdiArea->addSubWindow(pSubWidget);
	QMdiSubWindow* newSubWin = mdiArea->addSubWindow(pSubWidget);
	newSubWin->setProperty("FileFullName", strFileFullName);
	newSubWin->setWindowTitle(fileName);
	newSubWin->showMaximized();
	newSubWin->setMinimumSize(0, 0);
	newSubWin->setProperty("file", fileName);
	newSubWin->setWindowIcon(subWinIcon);
	if (subWin != nullptr)
	{
		*subWin = pSubWidget;
	}
	return 1;

}

int MDIMainWindow::DisplayDirFile(const QString& cfgFile, const QString & strDir)
{
	QMap<QString, QStandardItem*> m_NodeMap;

	QStringList filterList;
	QSettings cfg(cfgFile, QSettings::IniFormat);
	QString strRasterExtends = cfg.value("TYPE/raster_extends").toString();

	QStringList strExtends = strRasterExtends.split(";");
	for (int i = 0; i < strExtends.size(); i++)
	{
		filterList.push_back(QString::fromLocal8Bit("*.") + strExtends[i]);
	}

	QStringList strCurveExtends = cfg.value("TYPE/curve_extends").toString().split(";");
	for (int i = 0; i < strCurveExtends.size(); i++)
	{
		filterList.push_back(QString::fromLocal8Bit("*.") + strCurveExtends[i]);
	}

	QDir dir(strDir);

	QString strFolderName = dir.dirName();

	QStandardItem* rootItem = m_pStandardItemModel->invisibleRootItem();

	QStandardItem* folder = new QStandardItem(strFolderName);
	folder->setIcon(QIcon("./icon/parent.png"));
	folder->setData("3");

	rootItem->setChild(rootItem->rowCount(), folder);

	for (int i = 0; i < m_classify_count; i++)
	{
		QStandardItem* item = new QStandardItem(m_classify_name[i]);
		item->setIcon(QIcon("./icon/folder.png"));
		
		folder->setChild(folder->rowCount(), item);

		QStringList extends = m_classify_extend[i].split(";");
		for (int ii = 0; ii < extends.size(); ii++)
		{
			m_NodeMap.insert(extends[ii], item);
		}
	}

	QFileInfoList filesInfo = dir.entryInfoList(filterList, QDir::Files | QDir::NoDotAndDotDot);
	
	for (int i = 0; i < filesInfo.size(); i++)
	{
		QString strFileName = filesInfo[i].fileName();
		QString strFileSuffix = filesInfo[i].suffix();
		
		QStandardItem* pItem;
		pItem = m_NodeMap.value(strFileSuffix);
		if (pItem == nullptr) continue;
		int iIndex = pItem->rowCount();
		QStandardItem* pChild = new QStandardItem(strFileName);
		pChild->setToolTip(filesInfo[i].absoluteFilePath());

		QJsonObject jsonValue;
		
		QJsonValue pathValue(filesInfo[i].absoluteFilePath());
		QJsonValue openState(false);
		jsonValue.insert("path", pathValue);
		jsonValue.insert("state", openState);
		//jsonValue.insert("subwin", QJsonValue((qint64)0));

		pChild->setData(jsonValue);
		pChild->setIcon(QIcon("./icon/close.png"));
		
		pItem->setChild(iIndex, pChild);
	}
	m_setupUI.treeView->expandAll();

	return 0;
}

QMdiSubWindow* MDIMainWindow::GetMySubWindow(const QString & strFilePathName)
{
	//QList<QMdiSubWindow*> subWinList = m_setupUI.mdiArea->subWindowList();
	QList<QMdiSubWindow*> subWinList = mdiArea->subWindowList();
	for (int i = 0; i < subWinList.size(); i++)
	{
		QMdiSubWindow* pSubWin = subWinList.at(i);
		QString strFile = pSubWin->property("file").toString();
		if (strFilePathName == strFile)
		{
			return pSubWin;
		}
	}

	return false;
}

void MDIMainWindow::SaveToImageFile(QwtPlot * pPlot, const QString& strFile)
{
	QwtPlotRenderer renderer;

	QPixmap pix(800, 600);
	renderer.renderTo(pPlot, pix);
	pix.save(strFile);
}

int MDIMainWindow::RunAlgorithm1(const float* InputPoints, size_t inputLen, float** outputPoints, size_t* outputLen, const char* funName)
{
	PyObject *pModule, *pDict, *pFunc;

	//pName = PyBytes_FromString("clound_algorithm");
	pModule = PyImport_ImportModule("clound_algorithm");
	if (!pModule)
	{
		PyErr_Print();
	}
	pDict = PyModule_GetDict(pModule);
	if (!pDict)
	{
		return 0;
	}

	// 找出函数名为run_algorithm的函数  "run_CloundBase_algorithm"
	pFunc = PyDict_GetItemString(pDict, funName);
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		return 0;
	}

	PyObject* list = PyList_New(inputLen);
	for (size_t i = 0; i < inputLen; i++)
	{
		PyList_SetItem(list, i, Py_BuildValue("f", InputPoints[i]));
	}

	Py_ssize_t ss111 = PyList_Size(list);

	PyObject* pyArgs = PyTuple_New(1);
	PyTuple_SetItem(pyArgs, 0, list);
	PyObject* pRet = PyEval_CallObject(pFunc, pyArgs);

	if (PyErr_Occurred())
	{
		PyErr_Print();
		return 0;
	}


	//Py_DECREF(pRet);
	
	*outputLen = PyList_Size(pRet);

	*outputPoints = new float[*outputLen];

	for (size_t i = 0; i < *outputLen; i++)
	{
		PyObject* pv = PyList_GetItem(pRet, i);

		double dPv = PyFloat_AsDouble(pv);
		(*outputPoints)[i] = dPv;
	}

	return 1;
}

void MDIMainWindow::slot_openDir(bool)
{
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/open_dir2").toString();

	QString strDir = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("打开目录"), strDefalutOpenDir);

	if (strDir.size() == 0) return;

	DisplayDirFile("FileClassify.ini", strDir);//获取文件扩展名和分类信息

	if (strDir.size() != 0)
	{
		fileList.setValue("DEFALUTDIR/open_dir2", strDir);

		//fileList.be
		QString strRecentFile;
	}
}

void MDIMainWindow::slot_doubleClicked(const QModelIndex & index)
{
	QWidget* pSubWin = 0;
	QStandardItemModel* pSandardItemModel = dynamic_cast<QStandardItemModel*>(m_setupUI.treeView->model());
	QStandardItem* pItem = pSandardItemModel->itemFromIndex(index);

	QJsonObject jsonValue = pItem->data().toJsonObject();
	
	QString strFileNamePath = jsonValue.value("path").toString();
	bool bState = jsonValue.value("state").toBool();
	//qint64 subwin = jsonValue.value("subwin").toInt();

	QMdiSubWindow* pSubWindow = GetMySubWindow(strFileNamePath);

	if (pSubWindow)
	{
		pSubWindow->showMaximized();
		return;
	}
	else
	{
		if (OpenFile(strFileNamePath, &pSubWin))
		{
			AttachTreeItem* pBP = dynamic_cast<AttachTreeItem*>(pSubWin);
			if (pBP != nullptr)
			{
				/*QModelIndex mi = pSandardItemModel->indexFromItem(pItem->parent());
				pBP->SetModel(pSandardItemModel);
				pBP->SetRowNum(index.row());
				pBP->SetIndex(mi);*/

				pBP->SetItem(pItem);
			}
			pItem->setIcon(QIcon("./icon/opened.png"));
			jsonValue.insert("state", true);
			pItem->setData(jsonValue);
		}
	}
}

void MDIMainWindow::slot_save(bool)
{
	//QMdiSubWindow* pSubwin = m_setupUI.mdiArea->currentSubWindow();
	QMdiSubWindow* pSubwin = mdiArea->currentSubWindow();
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/save_dir").toString();
	if (strDefalutOpenDir.size() == 0)
	{
		strDefalutOpenDir = "./";
	}

	QString strFileExtend = pSubwin->property("FileFullName").toString();

	int iIndex = strFileExtend.lastIndexOf(".");

	QString strFileBaseName = strFileExtend.left(iIndex);
	QString strFileSuffixName = strFileExtend.right(strFileExtend.size() - iIndex - 1);
	QString saveFormat = m_FileSaveFormat.value(strFileSuffixName);

	QString strFullPath = strDefalutOpenDir + "/" + saveFormat.arg(strFileSuffixName).arg(strFileBaseName) + ".jpeg";

	QString files = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存图像文件"), strFullPath, "*.bmp *.jpeg *.png");

	QFileInfo fi(files);
	QString strPath = fi.absolutePath();
	fileList.setValue("DEFALUTDIR/save_dir", strPath);

	SaveFile(files, pSubwin);
}

void MDIMainWindow::SaveFile(const QString& strFile, QMdiSubWindow* pSubwin)
{
	
	if (!pSubwin) return;

	QwtPlot* plot = dynamic_cast<QwtPlot*>(pSubwin->widget());
	if (plot == 0)
	{
		QWidget* pW = pSubwin->widget();
		TableView* pTV = dynamic_cast<TableView*>(pW);
		QTabWidget* pTab = nullptr;

		if (pTV)
		{
			pTab = pTV->m_form.tabWidget;
		}

		if (pTab == 0)
		{
			pSubwin->showMaximized();
			QPixmap pixmap = pSubwin->grab();
			pixmap.save(strFile);
			return;
		}

		int iCount = pTab->count();

		for (int i = 0; i < iCount; i++)
		{
			QWidget* pWidget = pTab->widget(i);

			QwtPlot* plot = dynamic_cast<QwtPlot*>(pWidget);

			if (strFile.size() != 0)
			{
				QFileInfo fi(strFile);

				QString strDir = fi.absolutePath();
				QString strBasename = fi.baseName();

				QString strExtname = fi.suffix();

				if (strExtname.size() == 0) strExtname = "bmp";

				QString strFile = strDir + "/" + strBasename + QString("%1").arg(i) + "." + strExtname;
				SaveToImageFile(plot, strFile);

				QString strPath = fi.absolutePath();
			}
		}
	}
	else
	{
		if (strFile.size() != 0)
		{
			SaveToImageFile(plot, strFile);

			QFileInfo fi(strFile);
			QString strPath = fi.absolutePath();
			QString strExtname = fi.suffix();

			if (strExtname.size() == 0) strExtname = "bmp";

			strPath += ".bmp";
		}
	}
}

void MDIMainWindow::slot_saveall(bool)
{
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/save_dir").toString();
	if (strDefalutOpenDir.size() == 0)
	{
		strDefalutOpenDir = "./";
	}

	QString strDir= QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("保存文件的文件夹"), strDefalutOpenDir);

	//QList<QMdiSubWindow*> subWinList = m_setupUI.mdiArea->subWindowList();
	QList<QMdiSubWindow*> subWinList = mdiArea->subWindowList();

	QProgressDialog* pd = new QProgressDialog(this);
	pd->setWindowTitle(QString::fromLocal8Bit("正在保存图片..."));
	pd->setAutoClose(true);
	pd->setRange(0, subWinList.size());
	pd->setWindowModality(Qt::WindowModal);
	pd->setModal(true);
	pd->open();
	for (int i = 0; i < subWinList.size(); i++)
	{
		QMdiSubWindow* subWin = subWinList[i];

		QString strFileExtend = subWin->property("FileFullName").toString();

		int iIndex = strFileExtend.lastIndexOf(".");

		QString strFileBaseName = strFileExtend.left(iIndex);
		QString strFileSuffixName = strFileExtend.right(strFileExtend.size() - iIndex - 1);
		QString saveFormat = m_FileSaveFormat.value(strFileSuffixName);

		QString strFullPath = strDir + "/" + saveFormat.arg(strFileSuffixName).arg(strFileBaseName) + ".jpeg";

		pd->setLabelText(strFullPath);
		SaveFile(strFullPath, subWin);
		pd->setValue(i + 1);
		
		//Sleep(1000);
		//pd->update();
	}
	//pd->exec();
	pd->reset();

	delete pd;
	fileList.setValue("DEFALUTDIR/save_dir", strDir);
}

void MDIMainWindow::slot_mainSettings(bool)
{
	MainSettingsDialog ms;
	ms.exec();
}

void MDIMainWindow::slot_createColorTable(bool)
{
	ColorTableDialog ctd;
	ctd.exec();
}

void MDIMainWindow::slot_legendDataChanged(const QVariant & itemInfo, const QList<QwtLegendData>& data)
{
	
}

void MDIMainWindow::slot_TileWindows(bool)
{
	//m_setupUI.mdiArea->tileSubWindows();
	mdiArea->tileSubWindows();
	adjustSize();
	showMinimized();
	showMaximized();
}

void MDIMainWindow::slot_CascadeWindows(bool)
{
	//m_setupUI.mdiArea->cascadeSubWindows();
	mdiArea->cascadeSubWindows();
}

void MDIMainWindow::slot_CloseDir(bool)
{
	QModelIndex currentIndex = m_setupUI.treeView->currentIndex();

	QStandardItem* currentItem = m_pStandardItemModel->itemFromIndex(currentIndex);
	QVariant data = currentItem->data();

	if (data.type() == QVariant::String)
	{
		int iNodeDeep = data.toString().toInt();
		TraverseTreeAndClose(currentItem);

		m_pStandardItemModel->invisibleRootItem()->removeRow(currentIndex.row());
	}
}

void MDIMainWindow::slot_Exit(bool)
{
	this->close();
}

void MDIMainWindow::slot_CloseAllWinAction(bool)
{
	QList<QMdiSubWindow*> subWinList = mdiArea->subWindowList();

	for (int i = 0; i < subWinList.size(); i++)
	{
		QMdiSubWindow* subWin = subWinList[i];
		if (subWin) subWin->close();
	}

}

void MDIMainWindow::slot_subWindowActivated(QMdiSubWindow * window)
{
	if (window == nullptr) return;

	RasterPlot* plot = dynamic_cast<RasterPlot*>(window->widget());

	if (plot == nullptr)
	{
		SubWindow* subWin = dynamic_cast<SubWindow*>(window->widget());

		if (subWin == nullptr) return;
		plot = dynamic_cast<RasterPlot*>(subWin->GetMainWidget());

		if (plot == nullptr)
		{
			return;
		}
	}
	
	plot->ClearAttachRasterPlot();

	//QList<QMdiSubWindow*> subWinList = m_setupUI.mdiArea->subWindowList();
	QList<QMdiSubWindow*> subWinList = mdiArea->subWindowList();

	for (int i = 0; i < subWinList.size(); i++)
	{
		QMdiSubWindow* subWin = subWinList[i];

		RasterPlot* pOtherPlot = dynamic_cast<RasterPlot*>(subWin->widget());

		if (pOtherPlot == nullptr)
		{
			SubWindow* pMySubWin = dynamic_cast<SubWindow*>(subWin->widget());
			if (nullptr == pMySubWin) continue;

			pOtherPlot = dynamic_cast<RasterPlot*>(pMySubWin->GetMainWidget());
			if (pOtherPlot == nullptr) continue;
		}

		if (pOtherPlot && pOtherPlot != plot)
		{
			plot->AddAttachRasterPlot(pOtherPlot);
		}
	}
	//m_pCurrentWindow
	//disconnect()
	//m_pCurrentWindow = window;
}

QWidget * MDIMainWindow::MakeNewWidget(QWidget * leftWidget, const QString& strFile, const QString& strFileType)
{
	QMap<QString, QString> param = m_uiParameter.value(strFileType);
	SubWindow* Form = new SubWindow();
	
	Form->resize(716, 529);
	QGridLayout* gridLayout = new QGridLayout(Form);
	gridLayout->setObjectName(QStringLiteral("gridLayout"));
	gridLayout->setContentsMargins(1, 1, 1, 1);
	QHBoxLayout* horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(1);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

	horizontalLayout->addWidget(leftWidget);

	NonlinearityColorBarWidget* widget = new NonlinearityColorBarWidget(Form);

	QString strUnitName = m_RightAxisNames.value(strFileType);
	widget->SetUnitName(strUnitName);
	widget->SetParameter(param);
	widget->SetColorMap(strFile);
	widget->setObjectName(QStringLiteral("widget"));
	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
	widget->setSizePolicy(sizePolicy);


	QString strWidth = param.value("MinimumWidth");

	int iMinWidth = strWidth.toInt();
	widget->setMinimumSize(QSize(iMinWidth, 0));

	horizontalLayout->addWidget(widget);


	gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

	QMetaObject::connectSlotsByName(Form);

	Form->SetMainWidget(leftWidget);
	return Form;
}

void MDIMainWindow::TraverseTreeAndClose(QStandardItem * pTreeNode)
{
	if (!pTreeNode->hasChildren())
	{
		QJsonObject jsonValue = pTreeNode->data().toJsonObject();
		QString strFileNamePath = jsonValue.value("path").toString();
		QMdiSubWindow* pSubWindow = GetMySubWindow(strFileNamePath);

		if (pSubWindow)
		{
			pSubWindow->close();
			return;
		}
	}
	else
	{
		for (int i = 0; i < pTreeNode->rowCount(); i++)
		{
			TraverseTreeAndClose(pTreeNode->child(i));
		}
	}
	
}

void MDIMainWindow::slot_openFile(bool)
{
	QSettings fileList("filelist.ini", QSettings::IniFormat);

	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/open_dir").toString();
	QString strFileFilter = fileList.value("DEFALUTDIR/file_filter").toString();

	QStringList files = QFileDialog::getOpenFileNames(this, QString::fromLocal8Bit("打开文件"), strDefalutOpenDir, strFileFilter);
	if (files.size() == 0) return;

	if (files.size() > 0)
	{
		QString strFile = files[0];
		QFileInfo fileinfo(strFile);

		QString strPath = fileinfo.absolutePath();
		fileList.setValue("DEFALUTDIR/open_dir", strPath);
	}
	QFileInfo fi(files[0]);

	QString strOpenFileDirName = fi.dir().dirName();
	QStandardItem* rootItem = m_pStandardItemModel->invisibleRootItem();

	//QString strName = mainItem->text();

	QStandardItem* newMainItem = nullptr;
	
	for (int iChildIndex = 0; iChildIndex < rootItem->rowCount(); iChildIndex++)
	{
		QStandardItem* pItem = rootItem->child(iChildIndex);
	
		QString strNowFileDirName = pItem->text();

		if (strNowFileDirName == strOpenFileDirName)
		{
			newMainItem = pItem;
			break;
		}
	}

	if (!newMainItem)
	{
		newMainItem = new QStandardItem(strOpenFileDirName);
		rootItem->setChild(rootItem->rowCount(), newMainItem);
	}

	newMainItem->setIcon(QIcon("./icon/parent.png"));
	newMainItem->setData("2");

	for (int i = 0; i < files.size(); i++)
	{
		QString strFileName = files[i];
		QFileInfo fi(strFileName);
		QWidget* pSubWin = nullptr;
		OpenFile(strFileName, &pSubWin);

		QStandardItem* pChild = new QStandardItem(fi.fileName());
		pChild->setToolTip(strFileName);
		pChild->setData(strFileName);
		QJsonObject jsonValue;

		QJsonValue pathValue(strFileName);
		QJsonValue openState(true);
		jsonValue.insert("path", pathValue);
		jsonValue.insert("state", openState);
		
		pChild->setData(jsonValue);
		pChild->setIcon(QIcon("./icon/opened.png"));

		newMainItem->setChild(newMainItem->rowCount(), pChild);

		AttachTreeItem* pBP = dynamic_cast<AttachTreeItem*>(pSubWin);
		if (pBP != nullptr)
		{
			pBP->SetItem(pChild);
		}
	}

	m_setupUI.treeView->expandAll();
}

void FourWindowsFlat(QMdiArea* pMdiArea)
{
	QRect rect = pMdiArea->geometry();
	foreach(QMdiSubWindow *subWin, pMdiArea->subWindowList())
	{
		int iWidth = rect.width() / 2;
		int iHeight = rect.height() / 2;
	}
}