#pragma once
class ParseData
{
public:
	struct AdditionalData
	{
		char* buffer;
		size_t size;
	};

	enum DataType{RASTER, CURVE};
	ParseData();
	virtual ~ParseData();

	virtual bool ReadDataFromFile(const std::string& strFielName) = 0;
	virtual bool ReadDataFromMemory(const void* pData) = 0;
	virtual ParseData::DataType GetDataType() = 0;
	inline float* GetData() { return m_pData; }
	inline size_t GetDataSize() { return m_DataSize; }
	inline int GetDataColumnCount() { return m_ColumnCount; }
	inline void SetAxisProperty(float fXMin, float fXMax, float fYMin, float fYMax, float fZMin, float fZMax) {
		m_fXMin = fXMin;
		m_fXMax = fXMax;
		m_fYMin = fYMin;
		m_fYMax = fYMax;
		m_fZMin = fZMin;
		m_fZMax = fZMax;
	}
	inline void GetAxisProperty(float* fXMin, float* fXMax, float* fYMin, float* fYMax, float* fZMin, float* fZMax) {
		*fXMin = m_fXMin;
		*fXMax = m_fXMax;
		*fYMin = m_fYMin;
		*fYMax = m_fYMax;
		*fZMin = m_fZMin;
		*fZMax = m_fZMax;
	}

	inline void SetAxisComment(const std::string& strXComment, const std::string& strYComment, const std::string& strZComment) {
		m_strXComment = strXComment;
		m_strYComment = strYComment;
		m_strZComment = strZComment;
	}

	inline void GetAxisComment(std::string& strXComment, std::string& strYComment, std::string& strZComment)
	{
		strXComment = m_strXComment;
		strYComment = m_strYComment;
		strZComment = m_strZComment;
	}

	inline void SetTitle(const std::string& strTitle) { m_strTtile = strTitle; }

	inline void GetTitle(std::string& strTitle) { strTitle = m_strTtile; }

	inline AdditionalData* GetAdditionalData() { return m_OtherData; }

	inline void SetAxisInterval(float fXInterval, float fYInterval, float fZInterval)
	{
		m_fXInterval = fXInterval;
		m_fYInterval = fYInterval;
		m_fZInterval = fZInterval;
	}

	inline void GetAxisInterval(float* fXInterval, float* fYInterval, float* fZInterval)
	{
		*fXInterval = m_fXInterval;
		*fYInterval = m_fYInterval;
		*fZInterval = m_fZInterval;
	}
protected:
	float* m_pData;
	size_t m_DataSize;
	int m_ColumnCount;
	float m_fXMin;
	float m_fXMax;
	float m_fYMin;
	float m_fYMax;
	float m_fZMin;
	float m_fZMax;
	float m_fXInterval;
	float m_fYInterval;
	float m_fZInterval;

	std::string m_strXComment;
	std::string m_strYComment;
	std::string m_strZComment;

	std::string m_strTtile;

	AdditionalData* m_OtherData;
};

