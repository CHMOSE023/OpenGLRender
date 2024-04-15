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

//  设置射线的起点
void Ray::SetOrigin(const glm::vec3& origin)
{
	m_origin = origin;
}

// 设置射线的方向
void Ray::SetDirection(const glm::vec3& direction)
{

	m_direction = glm::normalize(direction);
}

// 获取射线的起点
glm::vec3 Ray::GetOrigin() const
{
	return m_origin;
}

// 获取射线的方向
glm::vec3 Ray::GetDirection() const
{
	return m_direction;
}

//  计算射线上的点
glm::vec3 Ray::PointAt(float t) const
{
	return m_origin + t * m_direction;

}
