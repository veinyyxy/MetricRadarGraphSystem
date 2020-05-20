#include "stdafx.h"
#include "RasterPlot.h"
#include "NonlinearityColorBarWidget.h"
#include "RadarPlotPicker.h"
#include "TimeScaleDraw.h"

class ColorTableScaleDraw : public QwtScaleDraw
{
public:
	double m_dDeleteLabel = -600000;
protected:
	virtual void drawLabel(QPainter * pPainter, double val) const
	{
		if (abs(m_dDeleteLabel - (-600000)) < 0.000001)
		{
			QwtScaleDraw::drawLabel(pPainter, val);
		}
		else
		{
			if (abs(m_dDeleteLabel - val) < 0.000001)
			{
				return;
			}
			else
			{
				QwtScaleDraw::drawLabel(pPainter, val);
			}
		}
	}
};

class DateScaleDraw : public QwtDateScaleDraw
{
public:
	DateScaleDraw(Qt::TimeSpec timeSpec) :
		QwtDateScaleDraw(timeSpec)
	{
		// as we have dates from 2010 only we use
		// format strings without the year

		setDateFormat(QwtDate::Millisecond, "hh:mm:ss:zzz");
		setDateFormat(QwtDate::Second, "hh:mm:ss");
		setDateFormat(QwtDate::Minute, "hh:mm");
		setDateFormat(QwtDate::Hour, "hh:mm");
		setDateFormat(QwtDate::Day, "ddd-dd-MMM");
		setDateFormat(QwtDate::Week, "Www");
		setDateFormat(QwtDate::Month, "MMM");
	}

	virtual QwtDate::IntervalType
		intervalType(const QwtScaleDiv &) const
	{
		return QwtDate::Hour;
	}
};

RasterPlot::RasterPlot( QWidget *parent ):
    BasicPlot( parent ), m_pRasterData(0), m_pColorMap(0)
{

	m_pMyMarker = new QwtPlotMarker();
	//m_pMyMarker->setLabel(QString::fromLatin1("y = 0"));
	m_pMyMarker->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
	m_pMyMarker->setLineStyle(QwtPlotMarker::Cross);
	
	//m_pMyMarker->setLabelOrientation(Qt::Orientation::Horizontal);
	//m_pMyMarker->setYValue(5.0);
	//m_pMyMarker->setXValue(15);
	//m_pMyMarker->attach(this);
	//m_pCurveSimulation = new QwtPlotCurve();
	//m_pCurveSimulation->setStyle(QwtPlotCurve::NoCurve);

	//m_pSymbolSimulation = new QwtSymbol();

	//m_pCurveSimulation->setSymbol(m_pSymbolSimulation);
	//m_pCurveSimulation->attach(this);
}

void RasterPlot::DrawPlot()
{
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setBorderRadius(10);
	QPalette canvasPalette(Qt::white);
	canvasPalette.setColor(QPalette::Foreground, QColor(255, 255, 255));
	canvas->setPalette(canvasPalette);
	setCanvas(canvas);
	
	d_spectrogram = new QwtPlotSpectrogram();
	d_spectrogram->setRenderThreadCount(0); // use system specific thread count

	d_spectrogram->setColorMap(m_pColorMap);

	d_spectrogram->setData(m_pRasterData);
	d_spectrogram->attach(this);
	//this->setAxisScaleEngine(QwtPlot::yRight, new NonlinearityColorBarWidget());
	const QwtInterval zInterval = d_spectrogram->data()->interval(Qt::ZAxis);
	// A color bar on the right axis
	QwtScaleWidget *rightAxis = this->axisWidget(QwtPlot::yRight);
	rightAxis->setColorBarEnabled(true);
	rightAxis->setColorBarWidth(40);

	rightAxis->setColorMap(zInterval, m_pAxisColorMap);

	setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue(), m_fYAxisSetp);
	enableAxis(QwtPlot::yRight);

	plotLayout()->setAlignCanvasToScales(true);

	//QwtDateScaleDraw *scaleDraw = new DateScaleDraw(Qt::UTC);
	//scaleDraw->setTimeSpec(Qt::TimeSpec::TimeZone);

	//QTime t = QTime::currentTime();
	TimeScaleDraw* timeScaleDraw = new TimeScaleDraw(m_StartDateTime.time());

	QwtDateScaleEngine *scaleEngine = new QwtDateScaleEngine(Qt::UTC);
	
	setAxisScaleDraw(QwtPlot::xBottom, timeScaleDraw);
	setAxisScaleEngine(QwtPlot::xBottom, scaleEngine);

	//setAxisLabelRotation(QwtPlot::xBottom, -50.0);
	setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter);
	setAxisScale(QwtPlot::xBottom, 0, 150.0, 30);
	setAxisMaxMinor(QwtPlot::xBottom, 1);
	setAxisScale(QwtPlot::yLeft, 0.0, 15.0, 1.0);
	setAxisMaxMinor(QwtPlot::yLeft, 0);

	QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(canvas);
	magnifier->setAxisEnabled(QwtPlot::yRight, false);

	QwtPlotPanner *panner = new QwtPlotPanner(canvas);
	panner->setAxisEnabled(QwtPlot::yRight, false);

	RadarPlotPicker* pPicker = new RadarPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
		QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
		this->canvas());
	//m_picker->setStateMachine(new QwtPickerDragPointMachine());
	pPicker->setRubberBandPen(QColor(Qt::green));
	pPicker->setRubberBand(QwtPicker::CrossRubberBand);
	pPicker->setTrackerPen(QColor(Qt::black));

	pPicker->SetData(m_pRasterData);
	pPicker->SetDateTime(m_StartDateTime);

	m_picker = pPicker;

	connect(m_picker, SIGNAL(CurrentPoint(const QPointF &)),
		SLOT(slot_CurrentPoint(const QPointF &)));
}

void RasterPlot::exportPlot()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "rasterview.jpg" );
}

void RasterPlot::setResampleMode( int mode )
{
	setCanvasBackground(QBrush(QColor(255, 255, 255)));
    //replot();
}

void RasterPlot::slot_CurrentPoint(const QPointF & pos)
{
	m_pMyMarker->detach();
	replot();
	QSet<RasterPlot*>::iterator s = m_OtherRasterPlot.begin();
	while (s != m_OtherRasterPlot.end())
	{
		
		(*s)->SetMarkerPoint(pos);
		s++;
	}
	//emit signal_CurrentPoint(pos);
}

void RasterPlot::SetRasterData(QwtMatrixRasterData* pRasterData)
{
	m_pRasterData = pRasterData;
}

void RasterPlot::SetColorMap(QwtColorMap* pColorMap)
{
	m_pColorMap = pColorMap;
}

void RasterPlot::showInfo(QString text)
{
	if (text == QString::null)
	{
		if (m_picker->rubberBand())
			text = "Cursor Pos: Press left mouse button in plot region";
		else
			text = "Zoom: Press mouse button and drag";
	}
}

inline void RasterPlot::SetMarkerPoint(const QPointF & pf)
{
	if (pf.x() > 150 / 2)
	{
		m_pMyMarker->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
	}
	else
	{
		m_pMyMarker->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
	}
	m_pMyMarker->setXValue(pf.x());
	m_pMyMarker->setYValue(pf.y());
	QString outText;
	double value = 0;
	if (m_pRasterData)
	{
		value = m_pRasterData->value(pf.x(), pf.y());
	}

	QString strHeight = QString("%1").arg(pf.y());
	QTime currentTime = m_StartDateTime.time().addSecs(pf.x()*60.0);
	QString strTimeText = QString("%1").arg(currentTime.toString("hh:mm:ss.zzz"));
	outText = QString::fromLocal8Bit("[") + strTimeText + ", "; 
	outText = outText + strHeight + QString::fromLocal8Bit(" KM") + "] = " + QString("%1").arg(value);

	QwtText qwtText;
	QFont markFont;
	markFont.setBold(true);
	markFont.setPixelSize(18);
	qwtText.setFont(markFont);
	qwtText.setText(outText);
	m_pMyMarker->setLabel(qwtText);
	
	m_pMyMarker->detach();
	m_pMyMarker->attach(this);
	this->replot();
}

void RasterPlot::SetHideLable(const double & hl)
{
	ColorTableScaleDraw* pCTSD = new ColorTableScaleDraw;
	pCTSD->m_dDeleteLabel = hl;

	setAxisScaleDraw(QwtPlot::yRight, pCTSD);
}
