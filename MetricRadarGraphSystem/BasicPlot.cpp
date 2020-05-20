#include "stdafx.h"
#include "BasicPlot.h"

BasicPlot::BasicPlot(QWidget * pP) : QwtPlot(pP)
{
	
}

BasicPlot::BasicPlot(const QwtText & title, QWidget * pP) : QwtPlot(title, pP)
{
}

BasicPlot::~BasicPlot()
{
}

void BasicPlot::closeEvent(QCloseEvent * event)
{
	ChangeItem();
}