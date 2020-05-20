#pragma once
#include "qwt_scale_widget.h"

class ColorBar;

class NonlinearityColorBarWidget :
	public QWidget
{
public:
	NonlinearityColorBarWidget(QWidget* p);
	~NonlinearityColorBarWidget();
	void SetColorMap(const QString& cfgFile);
	void SetParameter(const QMap<QString, QString>& parm);
	inline void SetUnitName(const QString& strUint) { m_strUint = strUint; }
protected:
	virtual void paintEvent(QPaintEvent * pe);
private:
	QString m_strUint;
	void DrawColorBar(int x, int y, int width, int height, QPainter* pPainter);
	ColorBar* m_pRadarColorMap;

	int HeightAdjust, FontSize, YOffset, XOffice, FontWidth, FontXOffset, FontYOffset;
};

