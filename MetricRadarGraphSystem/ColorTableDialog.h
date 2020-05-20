#pragma once
#include <QDialog>
#include "ui_MakeColorTable.h"

class ColorTableDialog : public QDialog
{
	Q_OBJECT
public:
	ColorTableDialog();
	~ColorTableDialog();
	Ui::Dialog m_setup;

	virtual void keyPressEvent(QKeyEvent *e);

public slots:
	void slot_cellClicked(int row, int column);
	void slot_cellDoubleClicked(int row, int column);

	void slot_cellChanged(int row, int column);

	void slot_clickView();

	void slot_save(bool);
	void slot_open(bool);
};

