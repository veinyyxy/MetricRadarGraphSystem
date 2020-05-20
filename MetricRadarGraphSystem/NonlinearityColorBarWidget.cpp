#include "stdafx.h"
#include "NonlinearityColorBarWidget.h"
#include "RadarColorMap.h"
#include "ConfigurableColorBar.h"

NonlinearityColorBarWidget::NonlinearityColorBarWidget(QWidget* p) : QWidget(p), m_pRadarColorMap(0)
{
}

NonlinearityColorBarWidget::~NonlinearityColorBarWidget()
{
}

void NonlinearityColorBarWidget::SetColorMap(const QString& cfgFile)
{
	m_pRadarColorMap = new ConfigurableColorBar();
	m_pRadarColorMap->LoadData(cfgFile.toStdString());
}

void NonlinearityColorBarWidget::SetParameter(const QMap<QString, QString>& parm)
{
	HeightAdjust = parm.value("HeightAdjust").toInt(); 
	FontSize = parm.value("FontSize").toInt(); 
	YOffset = parm.value("YOffset").toInt(); 
	XOffice = parm.value("XOffice").toInt(); 
	FontWidth = parm.value("FontWidth").toInt();
	FontXOffset = parm.value("FontXOffset").toInt();
	FontYOffset = parm.value("FontYOffset").toInt();
}

void NonlinearityColorBarWidget::paintEvent(QPaintEvent * pe)
{
	if (!m_pRadarColorMap) return;
	QSize WidgetSize = this->size();
	QPainter painter(this);
	QFont font = painter.font();
	font.setPixelSize(FontSize);
	painter.setFont(font);

	std::vector<float> ValueSet;
	m_pRadarColorMap->GetValueSet(&ValueSet);
	size_t ValueCount = ValueSet.size();

	int iRectHeight = (WidgetSize.height() - HeightAdjust) / ValueCount;

	QColor color;
	int iHCount = 0;
	for (int i = ValueCount - 2; i >= 0; i--)
	{
		int iH(0);
		float fV = ValueSet.at(i);
		m_pRadarColorMap->GetColor(fV, &color);

		painter.setBrush(QBrush(color));
		painter.drawRect(XOffice, YOffset + iRectHeight * iHCount, WidgetSize.width() - FontWidth, iRectHeight);
		//QRect rectangle(WidgetSize.width() - FontWidth, 27 + iRectHeight * iHCount, 60, 30);

		if (i == 0)
		{
			painter.drawText(WidgetSize.width() - FontWidth + FontXOffset, YOffset + iRectHeight * (iHCount + 1) + FontYOffset, m_strUint);
		}
		else
		{
			painter.drawText(WidgetSize.width() - FontWidth + FontXOffset, YOffset + iRectHeight * (iHCount + 1) + FontYOffset, QString("%1").arg(fV));
		}
		
		//painter.drawText(rectangle, Qt::AlignCenter,QString("%1").arg(fV));
		iHCount++;
	}
}

void NonlinearityColorBarWidget::DrawColorBar(int x, int y, int width, int height, QPainter * pPainter)
{
	QFont font = pPainter->font();
	font.setPixelSize(18);
	pPainter->setFont(font);

	std::vector<float> ValueSet;
	m_pRadarColorMap->GetValueSet(&ValueSet);
	size_t ValueCount = ValueSet.size();

	int iRectHeight = height / ValueCount;

	QColor color;
	int iHCount = 0;
	for (int i = ValueCount - 2; i >= 0; i--)
	{
		int iH(0);
		float fV = ValueSet.at(i);
		m_pRadarColorMap->GetColor(fV, &color);

		pPainter->setBrush(QBrush(color));
		pPainter->drawRect(0, iRectHeight * iHCount, width - 80, iRectHeight);
		QRect rectangle(width - 80 + 10, 27 + iRectHeight * iHCount, 60, 30);
		pPainter->drawText(width - 80 + 10, 27 + iRectHeight * iHCount, QString("%1").arg(fV));
		//painter.drawText(rectangle, Qt::AlignCenter,QString("%1").arg(fV));
		iHCount++;
	}
}

