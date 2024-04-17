#pragma once
#include <Windows.h>
class TimeStamp
{
public:
	TimeStamp()
	{
		::QueryPerformanceFrequency(&m_Frequency); // ��ȡ CPU �ĸ߾��ȼ�ʱ����Ƶ��
		::QueryPerformanceCounter(&m_Start);       // ��ȡ��ǰ CPU ���ڼ���ֵ
	}
	~TimeStamp() {};

	void Update()
	{
		::QueryPerformanceCounter(&m_Start);      // ��ȡ��ǰ CPU ���ڼ���ֵ
	}

	double   GetElapsedSecond() const              // ��ȡ����������
	{
		LARGE_INTEGER   cur;
		QueryPerformanceCounter(&cur);
		return  double(cur.QuadPart - m_Start.QuadPart) / double(m_Frequency.QuadPart);
	}

	
protected:
	LARGE_INTEGER   m_Start;
	LARGE_INTEGER   m_Frequency;

};

