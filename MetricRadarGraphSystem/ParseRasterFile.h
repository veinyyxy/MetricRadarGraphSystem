#pragma once
#include "ParseData.h"

#define INDEX_TO_COLOR(mix, mid, max) (((mid)-(mix))/((max)-(mix)))

#pragma pack(4)
typedef struct file_header
{
	char radar_name[32];// 32	1	32	雷达站名
	int mode;//	4	4	探测模式
	int years;//	4	4	开始探测时间(年)
	int months;//	4	4	开始探测时间(月)
	int days;//	4	4	开始探测时间(日)
	int hours;//	4	4	开始探测时间(时)
	int minutes;//	4	4	开始探测时间(分)
	int seconds;//	4	4	开始探测时间(秒)
	int yeare;//	4	4	结束探测时间(年)
	int monthe;//	4	4	结束探测时间(月)
	int daye;//	4	4	结束探测时间(日)
	int houre;//	4	4	结束探测时间(时)
	int minutee;//	4	4	结束探测时间(分)
	int seconde;//	4	4	结束探测时间(秒)
	float radlat;//		4	4	雷达维度°
	float radlon;//		4	4	雷达经度°
	float radhgt;//		4	4	雷达高度m
	float fstgatdis;//		4	4	第一个有效库距离m
	float nyq_vel;//	4	4	最大可测速度m / s
	float bin_vel;//	4	4	速度分辨率m / s
	float Prf1;//	4	4	脉冲重复频率一 hz
	float Prf2;//	4	4	脉冲重复频率二 hz
	float elev_angle;//	4	4	仰角°
	float azim_angle;//	4	4	方位°
	int Num_beam;//	Int	4	4	径向数
	int Num_gate;//	Int	4	4	每根径向的库数
	int gatelength;//	int	4	4	库长m
				   //char recordtime[17];//	每根径向的时间
} FILE_HEADER, *P_FILE_HEADER;
#pragma pack()
//	Char*num_beam* 20	1	Num_beam * 20
//Data	Float*num_beam
//*num_gate	1	Num_beam*
//num_gate	数据

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

