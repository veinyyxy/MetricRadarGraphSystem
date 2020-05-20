#include "stdafx.h"
#include "RadarCurveData.h"

#define DELETE_DATA(p) if(p) delete[] p

RadarCurveData::RadarCurveData()
{
	//dt = { 0 };
	memset(&dt, 0, sizeof(dt));
}

RadarCurveData::~RadarCurveData()
{
	DELETE_DATA(dt.recordtime);
	DELETE_DATA(dt.cloudlayer);
	DELETE_DATA(dt.Hcloudbase);
	DELETE_DATA(dt.Hcloudtop);
	DELETE_DATA(dt.Thickcloud);
	DELETE_DATA(dt.Classcloud);
	DELETE_DATA(dt.ichoice);
	DELETE_DATA(dt.Hbbmid);
	DELETE_DATA(dt.Hbblow);
	DELETE_DATA(dt.Hbbup);
	DELETE_DATA(dt.Z_bbtop);
	DELETE_DATA(dt.Z_bbmid);
	DELETE_DATA(dt.Z_bblow);
	DELETE_DATA(dt.vel_bbtop);
	DELETE_DATA(dt.vel_bbmid);
	DELETE_DATA(dt.vel_bblow);
	DELETE_DATA(dt.LDR_bbtop);
	DELETE_DATA(dt.LDr_bbmid);
	DELETE_DATA(dt.LDR_bblow);
}

bool RadarCurveData::ReadDataFromFile(const std::string & strFielName)
{
	//dt = { 0 };
	//fh = {0};
	memset(&dt, 0, sizeof(dt));
	memset(&fh, 0, sizeof(fh));
	QFile file(strFielName.c_str());
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	uint size = sizeof(file_header);
	QDataStream out(&file);
	int iRLen = out.readRawData((char*)&fh, size);

	char *times = new char[fh.Num_beam * 20]; memset(times, 0, fh.Num_beam * 20);
	out.readRawData(times, fh.Num_beam * 20);
	dt.recordtime = times;

	int* cloudLayer = new int[fh.Num_beam]; memset(cloudLayer, 0, fh.Num_beam * sizeof(int));
	out.readRawData((char*)cloudLayer, fh.Num_beam * sizeof(int));
	dt.cloudlayer = cloudLayer;

	float* Hcloudbase = new float[10 * fh.Num_beam]; memset(Hcloudbase, 0, sizeof(float) * 10 * fh.Num_beam);
	out.readRawData((char*)Hcloudbase, sizeof(float) * 10 * fh.Num_beam);
	dt.Hcloudbase = Hcloudbase;

	float* Hcloudtop = new float[10 * fh.Num_beam]; memset(Hcloudtop, 0, sizeof(float) * 10 * fh.Num_beam);
	out.readRawData((char*)Hcloudtop, sizeof(float) * 10 * fh.Num_beam);
	dt.Hcloudtop = Hcloudtop;

	float* Thickcloud = new float[10 * fh.Num_beam]; memset(Thickcloud, 0, sizeof(float) * 10 * fh.Num_beam);
	out.readRawData((char*)Thickcloud, sizeof(float) * 10 * fh.Num_beam);
	dt.Thickcloud = Thickcloud;

	char* Classcloud = new char[10 * fh.Num_beam * 2]; memset(Classcloud, 0, 10 * fh.Num_beam * 2);
	out.readRawData(Classcloud, 10 * fh.Num_beam * 2);
	dt.Classcloud = Classcloud;

	int* ichoice = new int[fh.Num_beam]; memset(ichoice, 0, sizeof(int) * fh.Num_beam);
	out.readRawData((char*)ichoice, sizeof(int) * fh.Num_beam);
	dt.ichoice = ichoice;

	float* Hbbmid = new float[fh.Num_beam]; memset(Hbbmid, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Hbbmid, sizeof(float) * fh.Num_beam);
	dt.Hbbmid = Hbbmid;

	float* Hbblow = new float[fh.Num_beam]; memset(Hbblow, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Hbblow, sizeof(float) * fh.Num_beam);
	dt.Hbblow = Hbblow;

	float* Hbbup = new float[fh.Num_beam]; memset(Hbbup, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Hbbup, sizeof(float) * fh.Num_beam);
	dt.Hbbup = Hbbup;

	float* Z_bbtop = new float[fh.Num_beam]; memset(Z_bbtop, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Z_bbtop, sizeof(float) * fh.Num_beam);
	dt.Z_bbtop = Z_bbtop;

	float* Z_bbmid = new float[fh.Num_beam]; memset(Z_bbmid, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Z_bbmid, sizeof(float) * fh.Num_beam);
	dt.Z_bbmid = Z_bbmid;

	float* Z_bblow = new float[fh.Num_beam]; memset(Z_bblow, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)Z_bblow, sizeof(float) * fh.Num_beam);
	dt.Z_bblow = Z_bblow;

	float* vel_bbtop = new float[fh.Num_beam]; memset(vel_bbtop, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)vel_bbtop, sizeof(float) * fh.Num_beam);
	dt.vel_bbtop = vel_bbtop;

	float* vel_bbmid = new float[fh.Num_beam]; memset(vel_bbmid, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)vel_bbmid, sizeof(float) * fh.Num_beam);
	dt.vel_bbmid = vel_bbmid;

	float* vel_bblow = new float[fh.Num_beam]; memset(vel_bblow, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)vel_bblow, sizeof(float) * fh.Num_beam);
	dt.vel_bblow = vel_bblow;

	float* LDR_bbtop = new float[fh.Num_beam]; memset(LDR_bbtop, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)LDR_bbtop, sizeof(float) * fh.Num_beam);
	dt.LDR_bbtop = LDR_bbtop;

	float* LDr_bbmid = new float[fh.Num_beam]; memset(LDr_bbmid, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)LDr_bbmid, sizeof(float) * fh.Num_beam);
	dt.LDr_bbmid = LDr_bbmid;

	float* LDR_bblow = new float[fh.Num_beam]; memset(LDR_bblow, 0, sizeof(float) * fh.Num_beam);
	out.readRawData((char*)LDR_bblow, sizeof(float) * fh.Num_beam);
	dt.LDR_bblow = LDR_bblow;

	return true;
}

bool RadarCurveData::ReadDataFromMemory(const void * pData)
{
	return false;
}
