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

// ����Ļ�ռ����һ��������
void Ray::ScreenPointToRay(const glm::dvec2& screenPoint, const glm::dmat4& projectionMatrix, const glm::dmat4& viewMatrix, const glm::dvec4& viewport)
{
    // ����Ļ�ռ�ת�����ü��ռ�
    double x = (2.0 * screenPoint.x - viewport.z) / viewport.z;
    double y = (2.0 * screenPoint.y - viewport.w) / viewport.w;
    glm::dvec4 rayClip(x, y, -1.0, 1.0);

    // �Ӳü��ռ�ת������ͼ�ռ�
    glm::dmat4 inverseProjectionMatrix = glm::inverse(projectionMatrix);
    glm::dvec4 rayView = inverseProjectionMatrix * rayClip;
    rayView = glm::dvec4(rayView.x, rayView.y, -1.0, 0.0); // ������������z������Ϊ������Ϊ��ͼ�ռ��е�z���ǳ�����Ļ���

    // ����ͼ�ռ�ת��������ռ�
    glm::dmat4 inverseViewMatrix = glm::inverse(viewMatrix);
    glm::dvec4 rayWorld = inverseViewMatrix * rayView;
    glm::dvec3 rayDirection = glm::normalize(glm::dvec3(rayWorld));

    m_origin    = glm::dvec3(0);
    m_direction = rayDirection;
    
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
