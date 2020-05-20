#include "stdafx.h"
#include "SubWindow.h"

SubWindow::SubWindow()
{
}

SubWindow::~SubWindow()
{
}

void SubWindow::closeEvent(QCloseEvent * event)
{
	ChangeItem();
}