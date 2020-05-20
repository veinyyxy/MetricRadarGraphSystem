#include "stdafx.h"
#include "MyLegend.h"
#include <Qwt_Legend_Label.h>

MyLegend::MyLegend(QWidget *parent)
{
}


MyLegend::~MyLegend()
{
}

void MyLegend::renderLegend(QPainter *p, const QRectF &r, bool fillBackground) const
{
	QwtLegend::renderLegend(p, r, fillBackground);
}

void MyLegend::renderItem(QPainter *p, const QWidget *w, const QRectF &r, bool fillBackground) const
{
	QwtLegend::renderItem(p, w, r, fillBackground);
}

void MyLegend::updateLegend(const QVariant &itemInfo, const QList<QwtLegendData> &data)
{
	QList <QwtLegendData> newData;

	for (int i = 0; i < data.size(); i++)
	{
		QwtText t = data.at(i).title();
		if (t.text().size() != 0)
		{
			newData.push_back(data.at(i));
		}
	}

	QwtLegend::updateLegend(itemInfo, newData);
}