#pragma once
#include<glm/glm.hpp>
class Frustum 
{
public:
    Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);  
    bool isPointInside(const glm::vec3& point) const;                                     // 判断点是否在视锥体内部    
    bool isSphereInside(const glm::vec3& center, float radius) const;                     // 判断包围球是否在视锥体内部   
    bool isBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const; // 判断包围盒是否在视锥体内部
private:
    glm::vec4 planes[6]; // 视锥体的六个平面
};

