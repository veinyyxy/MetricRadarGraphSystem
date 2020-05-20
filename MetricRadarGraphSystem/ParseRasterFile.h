#pragma once
#include "ParseData.h"

#define INDEX_TO_COLOR(mix, mid, max) (((mid)-(mix))/((max)-(mix)))

#pragma pack(4)
typedef struct file_header
{
	char radar_name[32];// 32	1	32	�״�վ��
	int mode;//	4	4	̽��ģʽ
	int years;//	4	4	��ʼ̽��ʱ��(��)
	int months;//	4	4	��ʼ̽��ʱ��(��)
	int days;//	4	4	��ʼ̽��ʱ��(��)
	int hours;//	4	4	��ʼ̽��ʱ��(ʱ)
	int minutes;//	4	4	��ʼ̽��ʱ��(��)
	int seconds;//	4	4	��ʼ̽��ʱ��(��)
	int yeare;//	4	4	����̽��ʱ��(��)
	int monthe;//	4	4	����̽��ʱ��(��)
	int daye;//	4	4	����̽��ʱ��(��)
	int houre;//	4	4	����̽��ʱ��(ʱ)
	int minutee;//	4	4	����̽��ʱ��(��)
	int seconde;//	4	4	����̽��ʱ��(��)
	float radlat;//		4	4	�״�ά�ȡ�
	float radlon;//		4	4	�״ﾭ�ȡ�
	float radhgt;//		4	4	�״�߶�m
	float fstgatdis;//		4	4	��һ����Ч�����m
	float nyq_vel;//	4	4	���ɲ��ٶ�m / s
	float bin_vel;//	4	4	�ٶȷֱ���m / s
	float Prf1;//	4	4	�����ظ�Ƶ��һ hz
	float Prf2;//	4	4	�����ظ�Ƶ�ʶ� hz
	float elev_angle;//	4	4	���ǡ�
	float azim_angle;//	4	4	��λ��
	int Num_beam;//	Int	4	4	������
	int Num_gate;//	Int	4	4	ÿ������Ŀ���
	int gatelength;//	int	4	4	�ⳤm
				   //char recordtime[17];//	ÿ�������ʱ��
} FILE_HEADER, *P_FILE_HEADER;
#pragma pack()
//	Char*num_beam* 20	1	Num_beam * 20
//Data	Float*num_beam
//*num_gate	1	Num_beam*
//num_gate	����

class ParseRasterFile :
	public ParseData
{
public:
	ParseRasterFile();
	~ParseRasterFile();
	virtual bool ReadDataFromFile(const std::string& strFielName);
	virtual bool ReadDataFromMemory(const void* pData);
	virtual ParseData::DataType GetDataType();
	QString m_strStationName;
	QString m_strExpression;
};

