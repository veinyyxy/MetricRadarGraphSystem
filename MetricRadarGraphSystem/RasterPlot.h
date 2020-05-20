#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include "BasicPlot.h"

class RasterPlot : public BasicPlot
{
	Q_OBJECT
public:
	RasterPlot( QWidget * = NULL );
	void SetRasterData(QwtMatrixRasterData* pRasterData);
	void SetColorMap(QwtColorMap* pColorMap);
	inline void SetAxisColorMap(QwtColorMap* pColorMap) { m_pAxisColorMap = pColorMap; }

	void DrawPlot();
	inline void SetStartDateTime(const QDateTime& t) { m_StartDateTime = t; }
	void showInfo(QString text);
	inline void SetValueSetp(float fS) { m_fYAxisSetp = fS; }
	inline void HideMarker(bool bH) { bH ? m_pMyMarker->attach(this) : m_pMyMarker->detach(); }
	inline void SetMarkerPoint(const QPointF& pf);
	inline void ClearAttachRasterPlot() { m_OtherRasterPlot.clear(); }
	inline void AddAttachRasterPlot(RasterPlot* pRP) { m_OtherRasterPlot.insert(pRP); }
	void SetHideLable(const double& hl);

public Q_SLOTS:
    void exportPlot();
    void setResampleMode( int );
	void slot_CurrentPoint(const QPointF & pos);
Q_SIGNALS:
	void signal_CurrentPoint(const QPointF & pos);

private:
    QwtPlotSpectrogram *d_spectrogram;
	QwtMatrixRasterData* m_pRasterData;
	QwtColorMap* m_pColorMap;
	QwtColorMap* m_pAxisColorMap;
	QDateTime m_StartDateTime;
	QwtPlotPicker *m_picker;
	float m_fYAxisSetp;
	/*QwtSymbol* m_pSymbolSimulation;
	QwtPlotCurve *m_pCurveSimulation;*/
	QwtPlotMarker* m_pMyMarker;
	QSet<RasterPlot*> m_OtherRasterPlot;
};
