#pragma once
#include "qwt_plot.h"
#include "AttachTreeItem.h"

class BasicPlot :
	public QwtPlot, public AttachTreeItem
{
public:
	BasicPlot(QWidget * pP = NULL);
	BasicPlot(const QwtText &title, QWidget * pP = NULL);
	~BasicPlot();
	
	void closeEvent(QCloseEvent *event);
};

