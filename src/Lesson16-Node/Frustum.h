#pragma once
#include<glm/glm.hpp>
class Frustum 
{
public:
    Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);  
    bool IsPointInside(const glm::vec3& point) const;                                     // �жϵ��Ƿ�����׶���ڲ�    
    bool IsSphereInside(const glm::vec3& center, float radius) const;                     // �жϰ�Χ���Ƿ�����׶���ڲ�   
    bool IsBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const; // �жϰ�Χ���Ƿ�����׶���ڲ�
private:
    glm::vec4 m_planes[6]; // ��׶�������ƽ��
};

