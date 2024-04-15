#pragma once
#include <glm/glm.hpp>
/// <summary>
/// 射线类
/// </summary>
class Ray
{
public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	~Ray() {};

public:
	void SetOrigin(const glm::vec3& origin);      // 设置射线的起点	
	void SetDirection(const glm::vec3& direction);// 设置射线的方向
	glm::vec3 GetOrigin() const;                   // 获取射线的方向
	glm::vec3 GetDirection() const;                // 
	glm::vec3 PointAt(float t) const;
	
public:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
};
