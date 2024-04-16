#include  "CameraBase.h"
#include  <Windows.h>
CameraBase::CameraBase()
{
	// vec3��ʼ��
	m_eye   = glm::dvec3(0.0f);
	m_look  = glm::dvec3(0.0f);;
	m_up    = glm::dvec3(0.0f);;
	m_right = glm::dvec3(0.0f);;
	m_moveSpeed = 3.0f;
}

CameraBase::~CameraBase()
{
}

void CameraBase::UpdateCamera(double fElapsed, int key)
{
	glm::dvec3 tempLook = m_eye;
	glm::dvec3 dir      = m_look - m_eye;

	dir = glm::normalize(dir); // ��һ����ָ�������ĳ�������Ϊ1��ͬʱ�����䷽�򲻱�

	if (265 == key) // �ϼ�
	{
		m_eye -= (dir * - m_moveSpeed) * fElapsed;
		m_look -= (dir * - m_moveSpeed) * fElapsed;
	}

	if (264 == key) // �¼�
	{
		m_eye += (dir * - m_moveSpeed) * fElapsed;
		m_look += (dir * - m_moveSpeed) * fElapsed;
	}

	if (262 == key) // ���
	{
		m_eye -= (m_right * m_moveSpeed) * fElapsed;
		m_look -= (m_right * m_moveSpeed) * fElapsed;
	}

	if (263 == key) // �Ҽ�
	{
		m_eye += (m_right * m_moveSpeed) * fElapsed;
		m_look += (m_right * m_moveSpeed) * fElapsed;
	}


	m_view = glm::lookAt(m_eye, m_look, m_up);
}

void CameraBase::UpdateCamera(double fElapsed)
{
	glm::dvec3 tempLook  = m_eye;
	glm::dvec3 dir       = m_look - m_eye;

	dir = glm::normalize(dir); // ��һ����ָ�������ĳ�������Ϊ1��ͬʱ�����䷽�򲻱�

	unsigned char keys[256];
	if (GetKeyboardState(keys)) 
	{

		if (keys[VK_UP] & 0x80)
		{
			m_eye  -= (dir * -m_moveSpeed) * fElapsed;
			m_look -= (dir * -m_moveSpeed) * fElapsed;
		}

		if (keys[VK_DOWN] & 0x80)
		{
			m_eye  += (dir * -m_moveSpeed) * fElapsed;
			m_look += (dir * -m_moveSpeed) * fElapsed;
		}

		if (keys[VK_LEFT] & 0x80)
		{
			m_eye  -= (m_right * m_moveSpeed) * fElapsed;
			m_look -= (m_right * m_moveSpeed) * fElapsed;
		}
		if (keys[VK_RIGHT] & 0x80)
		{
			m_eye  += (m_right * m_moveSpeed) * fElapsed;
			m_look += (m_right * m_moveSpeed) * fElapsed;
		}
	}

	
	m_view = glm::lookAt(m_eye,m_look,m_up);

}
