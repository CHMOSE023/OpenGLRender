#pragma once
#include<glm/glm.hpp>
class Frustum 
{
public:
    Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);  
    bool isPointInside(const glm::vec3& point) const;                                     // �жϵ��Ƿ�����׶���ڲ�    
    bool isSphereInside(const glm::vec3& center, float radius) const;                     // �жϰ�Χ���Ƿ�����׶���ڲ�   
    bool isBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const; // �жϰ�Χ���Ƿ�����׶���ڲ�
private:
    glm::vec4 planes[6]; // ��׶�������ƽ��
};

