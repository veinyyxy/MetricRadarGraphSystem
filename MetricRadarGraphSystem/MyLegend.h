#pragma once
#include "qwt_legend.h"
class MyLegend :
	public QwtLegend
{
	Q_OBJECT
public:
	MyLegend(QWidget *parent = NULL);
	~MyLegend();
	virtual void renderLegend(QPainter *,
		const QRectF &, bool fillBackground) const;

	virtual void renderItem(QPainter *,
		const QWidget *, const QRectF &, bool fillBackground) const;

public Q_SLOTS:
	virtual void updateLegend(const QVariant &itemInfo, const QList<QwtLegendData> &data);
};

