#pragma once
#include "CurveData.h"
class RadarCurveData :
	public CurveData
{
	struct file_header
	{
		char radar_name[32];	  //�״�վ��
		int intmode;			  //̽��ģʽ
		int intyears;			  //��ʼ̽��ʱ��(��)
		int intmonths;			  //��ʼ̽��ʱ��(��)
		int intdays;			  //��ʼ̽��ʱ��(��)
		int inthours;			  //��ʼ̽��ʱ��(ʱ)
		int intminutes;			  //��ʼ̽��ʱ��(��)
		int intseconds;			  //��ʼ̽��ʱ��(��)
		int intyeare;			  //����̽��ʱ��(��)
		int intmonthe;			  //����̽��ʱ��(��)
		int intdaye;			  //����̽��ʱ��(��)
		int inthoure;			  //����̽��ʱ��(ʱ)
		int intminutee;			  //����̽��ʱ��(��)
		int intseconde;			  //����̽��ʱ��(��)
		float radlat;			  //�״�ά�ȡ�
		float radlon;			  //�״ﾭ�ȡ�
		float radhgt;			  //�״�߶�m
		float fstgatdis;		  //��һ����Ч�����m
		float nyq_vel;			  //���ɲ��ٶ�m / s
		float bin_vel;			  //�ٶȷֱ���m / s
		float Prf1;				  //�����ظ�Ƶ��һ hz
		float Prf2;				  //�����ظ�Ƶ�ʶ� hz
		float elev_angle;		  //���ǡ�
		float azim_angle;		  //��λ��
		int Num_beam;			  //������
		int Num_gate;			  //ÿ������Ŀ���
		int gatelength;			  //�ⳤm
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

