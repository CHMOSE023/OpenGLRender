#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

class AABB {
public:
    // 构造函数
    AABB();
    AABB(const glm::vec3& min, const glm::vec3& max);

    // 获取最小顶点坐标
    glm::vec3 GetMinCorner() const;

    // 获取最大顶点坐标
    glm::vec3 GetMaxCorner() const;

    // 获取包围盒的中心点
    glm::vec3 GetCenter() const;

    // 获取包围盒的尺寸
    glm::vec3 GetSize() const;

    // 计算包围盒的体积
    float GetVolume() const;

    // 计算包围盒的表面积
    float GetSurfaceArea() const;

    // 检查点是否在包围盒内
    bool Contains(const glm::vec3& point) const;

    // 合并两个包围盒，返回新的包围盒
    AABB Merge(const AABB& other) const;

    // 检查两个包围盒是否相交
    bool Intersects(const AABB& other) const;

    // 包围盒变换
    void Transform(const glm::mat4& matrix);

    // 从点云生成包围盒
    static AABB FromPointCloud(const std::vector<glm::vec3>& points);

private:
    glm::vec3 m_minCorner; // 最小顶点
    glm::vec3 m_maxCorner; // 最大顶点
};
