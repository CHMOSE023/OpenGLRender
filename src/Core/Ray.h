#pragma once
#include <glm/glm.hpp>
/// <summary>
/// ������
/// </summary>
class Ray
{
public:
    Ray();
    Ray(const glm::vec3& origin, const glm::vec3& direction);
  ~Ray() {};

public:
    void SetOrigin(const glm::vec3& origin);      // �������ߵ����	
    void SetDirection(const glm::vec3& direction);// �������ߵķ���
    void ScreenPointToRay(                        // ����Ļ�ռ����һ��������
        const glm::dvec2& screenPoint,
        const glm::dmat4& projectionMatrix,
        const glm::dmat4& viewMatrix, 
        const glm::dvec4& viewport
    );

    glm::vec3 GetOrigin() const;                   // ��ȡ���ߵķ���
    glm::vec3 GetDirection() const;                // 
    glm::vec3 PointAt(float t) const;

public:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};
