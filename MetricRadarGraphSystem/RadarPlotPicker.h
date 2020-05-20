#pragma once
#include "qwt_plot_picker.h"
class RadarPlotPicker :
	public QwtPlotPicker
{
	Q_OBJECT

public:
	explicit RadarPlotPicker(QWidget *canvas);
	explicit RadarPlotPicker(int xAxis, int yAxis, QWidget * canvas);

	explicit RadarPlotPicker(int xAxis, int yAxis,
		RubberBand rubberBand, DisplayMode trackerMode, QWidget * canvas);
	~RadarPlotPicker();

	inline void SetData(QwtMatrixRasterData* data) { m_pMyData = data; }
	inline void SetDateTime(const QDateTime& dt) { m_StartTime = dt; }

protected:
	virtual QwtText trackerText(const QPoint &) const;
	virtual QwtText trackerTextF(const QPointF &) const;

	virtual void move(const QPoint &);
	virtual void append(const QPoint &);
	virtual bool end(bool ok = true);

Q_SIGNALS:
	void CurrentPoint(const QPointF & posF) const;

private:
	QwtMatrixRasterData* m_pMyData;
	QDateTime m_StartTime;
};

