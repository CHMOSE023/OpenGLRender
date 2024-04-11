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

//  设置射线的起点
void Ray::SetOrigin(const glm::vec3& origin)
{
	m_Origin = origin;
}

// 设置射线的方向
void Ray::SetDirection(const glm::vec3& direction)
{

	m_Direction = glm::normalize(direction);
}

// 获取射线的起点
glm::vec3 Ray::GetOrigin() const
{
	return m_Origin;
}

// 获取射线的方向
glm::vec3 Ray::GetDirection() const
{
	return m_Direction;
}

//  计算射线上的点
glm::vec3 Ray::PointAt(float t) const
{
	return m_Origin + t * m_Direction;

}
