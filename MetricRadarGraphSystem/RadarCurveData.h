#pragma once
#include "CurveData.h"
class RadarCurveData :
	public CurveData
{
	struct file_header
	{
		char radar_name[32];	  //雷达站名
		int intmode;			  //探测模式
		int intyears;			  //开始探测时间(年)
		int intmonths;			  //开始探测时间(月)
		int intdays;			  //开始探测时间(日)
		int inthours;			  //开始探测时间(时)
		int intminutes;			  //开始探测时间(分)
		int intseconds;			  //开始探测时间(秒)
		int intyeare;			  //结束探测时间(年)
		int intmonthe;			  //结束探测时间(月)
		int intdaye;			  //结束探测时间(日)
		int inthoure;			  //结束探测时间(时)
		int intminutee;			  //结束探测时间(分)
		int intseconde;			  //结束探测时间(秒)
		float radlat;			  //雷达维度°
		float radlon;			  //雷达经度°
		float radhgt;			  //雷达高度m
		float fstgatdis;		  //第一个有效库距离m
		float nyq_vel;			  //最大可测速度m / s
		float bin_vel;			  //速度分辨率m / s
		float Prf1;				  //脉冲重复频率一 hz
		float Prf2;				  //脉冲重复频率二 hz
		float elev_angle;		  //仰角°
		float azim_angle;		  //方位°
		int Num_beam;			  //径向数
		int Num_gate;			  //每根径向的库数
		int gatelength;			  //库长m
	};

	struct curve_data
	{
		char* recordtime;
		int *cloudlayer;
		float* Hcloudbase;
		float* Hcloudtop;
		float* Thickcloud;
		char* Classcloud;
		int* ichoice;
		float* Hbbmid;
		float* Hbblow;
		float* Hbbup;
		float* Z_bbtop;
		float* Z_bbmid;
		float* Z_bblow;
		float* vel_bbtop;
		float* vel_bbmid;
		float* vel_bblow;
		float* LDR_bbtop;
		float* LDr_bbmid;
		float* LDR_bblow;
	};
public:
	RadarCurveData();
	virtual ~RadarCurveData();

	// Inherited via CurveData
	virtual bool ReadDataFromFile(const std::string & strFielName) override;
	virtual bool ReadDataFromMemory(const void * pData) override;
	curve_data dt;
	file_header fh;
};

