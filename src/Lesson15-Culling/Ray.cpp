#include"Ray.h"

Ray::Ray()
{
	m_Origin = glm::vec3(0);
	m_Direction = glm::vec3(0);
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
{
	m_Origin = origin;
	m_Direction = direction;
}

//  �������ߵ����
void Ray::SetOrigin(const glm::vec3& origin)
{
	m_Origin = origin;
}

// �������ߵķ���
void Ray::SetDirection(const glm::vec3& direction)
{

	m_Direction = glm::normalize(direction);
}

// ��ȡ���ߵ����
glm::vec3 Ray::GetOrigin() const
{
	return m_Origin;
}

// ��ȡ���ߵķ���
glm::vec3 Ray::GetDirection() const
{
	return m_Direction;
}

//  ���������ϵĵ�
glm::vec3 Ray::PointAt(float t) const
{
	return m_Origin + t * m_Direction;

}
