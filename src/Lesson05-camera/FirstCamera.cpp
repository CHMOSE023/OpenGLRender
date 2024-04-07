#include "FirstCamera.h"
//#include <WinUser.h>
#include <Windows.h>
FirstCamera::FirstCamera()
{
	// vec3初始化
	m_Eye       = glm::vec3(0.0f);
	m_Look      = glm::vec3(0.0f);;
	m_Up        = glm::vec3(0.0f);;
	m_Right     = glm::vec3(0.0f);;
	m_MoveSpeed = 3.0f;
}

FirstCamera::~FirstCamera()
{
}

void FirstCamera::UpdateCamera(float fElapsed,int key)
{
	glm::vec3 tempLook = m_Eye;
	glm::vec3 dir      = m_Look - m_Eye;
	
	dir = glm::normalize(dir); // 归一化是指将向量的长度缩放为1，同时保持其方向不变

	if (265 == key) // 上键
	{
		m_Eye  -= (dir * -m_MoveSpeed) * fElapsed;
		m_Look -= (dir * -m_MoveSpeed) * fElapsed;
	}

	if (264 == key) // 下键
	{
		m_Eye  += (dir * -m_MoveSpeed) * fElapsed;
		m_Look += (dir * -m_MoveSpeed) * fElapsed;
	}

	if (262 == key) // 左键
	{
		m_Eye  -= (m_Right * m_MoveSpeed) * fElapsed;
		m_Look -= (m_Right * m_MoveSpeed) * fElapsed;
	}

	if (263 == key) // 右键
	{
		m_Eye  += (m_Right * m_MoveSpeed) * fElapsed;
		m_Look += (m_Right * m_MoveSpeed) * fElapsed;
	}

}

void FirstCamera::UpdateCamera(float fElapsed)
{
	glm::vec3 tempLook = m_Eye;
	glm::vec3 dir = m_Look - m_Eye;

	dir = glm::normalize(dir); // 归一化是指将向量的长度缩放为1，同时保持其方向不变

	unsigned char keys[256];
	if (GetKeyboardState(keys)) {

		if (keys[VK_UP] & 0x80)
		{
			m_Eye -= (dir * -m_MoveSpeed) * fElapsed;
			m_Look -= (dir * -m_MoveSpeed) * fElapsed;
		}

		if (keys[VK_DOWN] & 0x80)
		{
			m_Eye += (dir * -m_MoveSpeed) * fElapsed;
			m_Look += (dir * -m_MoveSpeed) * fElapsed;
		}

		if (keys[VK_LEFT] & 0x80)
		{
			m_Eye -= (m_Right * m_MoveSpeed) * fElapsed;
			m_Look -= (m_Right * m_MoveSpeed) * fElapsed;
		}
		if (keys[VK_RIGHT] & 0x80)
		{
			m_Eye += (m_Right * m_MoveSpeed) * fElapsed;
			m_Look += (m_Right * m_MoveSpeed) * fElapsed;
		}
	}
	
	

}
