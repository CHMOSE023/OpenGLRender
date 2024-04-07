#include "FirstCamera.h"
//#include <WinUser.h>
#include <Windows.h>
FirstCamera::FirstCamera()
{
	// vec3��ʼ��
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
	
	dir = glm::normalize(dir); // ��һ����ָ�������ĳ�������Ϊ1��ͬʱ�����䷽�򲻱�

	if (265 == key) // �ϼ�
	{
		m_Eye  -= (dir * -m_MoveSpeed) * fElapsed;
		m_Look -= (dir * -m_MoveSpeed) * fElapsed;
	}

	if (264 == key) // �¼�
	{
		m_Eye  += (dir * -m_MoveSpeed) * fElapsed;
		m_Look += (dir * -m_MoveSpeed) * fElapsed;
	}

	if (262 == key) // ���
	{
		m_Eye  -= (m_Right * m_MoveSpeed) * fElapsed;
		m_Look -= (m_Right * m_MoveSpeed) * fElapsed;
	}

	if (263 == key) // �Ҽ�
	{
		m_Eye  += (m_Right * m_MoveSpeed) * fElapsed;
		m_Look += (m_Right * m_MoveSpeed) * fElapsed;
	}

}

void FirstCamera::UpdateCamera(float fElapsed)
{
	glm::vec3 tempLook = m_Eye;
	glm::vec3 dir = m_Look - m_Eye;

	dir = glm::normalize(dir); // ��һ����ָ�������ĳ�������Ϊ1��ͬʱ�����䷽�򲻱�

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
