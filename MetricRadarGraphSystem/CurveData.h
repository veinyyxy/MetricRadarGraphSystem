#pragma once
class CurveData
{
public:
	CurveData();
	virtual ~CurveData();
	virtual bool ReadDataFromFile(const std::string& strFielName) = 0;
	virtual bool ReadDataFromMemory(const void* pData) = 0;
	inline void SetColumnCount(uint count) { m_ColumnCount = count; }
	inline uint GetColumnCount() { return m_ColumnCount; }
	void AppendValueVector(float* pValues);

protected:
	uint m_ColumnCount;
	std::vector<float*> m_ValueVector;
};

