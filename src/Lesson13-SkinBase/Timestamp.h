#pragma once
#include <Windows.h>
class Timestamp
{
public:
	Timestamp() 
	{
		::QueryPerformanceFrequency(&m_Frequency); // 获取 CPU 的高精度计时器的频率
		::QueryPerformanceCounter(&m_Start);       // 获取当前 CPU 周期计数值
	}
	~Timestamp() {};

	void Update()
	{
		::QueryPerformanceCounter(&m_Start);      // 获取当前 CPU 周期计数值
	}

	double   GetElapsedSecond() const              // 获取经过的秒数
	{
		LARGE_INTEGER   cur;
		QueryPerformanceCounter(&cur);
		return  double(cur.QuadPart - m_Start.QuadPart) / double(m_Frequency.QuadPart);
	}

	
protected:
	LARGE_INTEGER   m_Start;
	LARGE_INTEGER   m_Frequency;

};

