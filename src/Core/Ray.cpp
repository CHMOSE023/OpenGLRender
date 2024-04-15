#include"Ray.h"

Ray::Ray()
{
	m_origin = glm::vec3(0);
	m_direction = glm::vec3(0);
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
{
	m_origin = origin;
	m_direction = direction;
}

//  �������ߵ����
void Ray::SetOrigin(const glm::vec3& origin)
{
	m_origin = origin;
}

// �������ߵķ���
void Ray::SetDirection(const glm::vec3& direction)
{

	m_direction = glm::normalize(direction);
}

// ��ȡ���ߵ����
glm::vec3 Ray::GetOrigin() const
{
	return m_origin;
}

// ��ȡ���ߵķ���
glm::vec3 Ray::GetDirection() const
{
	return m_direction;
}

//  ���������ϵĵ�
glm::vec3 Ray::PointAt(float t) const
{
	return m_origin + t * m_direction;

}
