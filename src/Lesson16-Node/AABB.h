#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

class AABB {
public:
    // ���캯��
    AABB();
    AABB(const glm::vec3& min, const glm::vec3& max);

    // ��ȡ��С��������
    glm::vec3 GetMinCorner() const;

    // ��ȡ��󶥵�����
    glm::vec3 GetMaxCorner() const;

    // ��ȡ��Χ�е����ĵ�
    glm::vec3 GetCenter() const;

    // ��ȡ��Χ�еĳߴ�
    glm::vec3 GetSize() const;

    // �����Χ�е����
    float GetVolume() const;

    // �����Χ�еı����
    float GetSurfaceArea() const;

    // �����Ƿ��ڰ�Χ����
    bool Contains(const glm::vec3& point) const;

    // �ϲ�������Χ�У������µİ�Χ��
    AABB Merge(const AABB& other) const;

    // ���������Χ���Ƿ��ཻ
    bool Intersects(const AABB& other) const;

    // ��Χ�б任
    void Transform(const glm::mat4& matrix);

    // �ӵ������ɰ�Χ��
    static AABB FromPointCloud(const std::vector<glm::vec3>& points);

private:
    glm::vec3 m_minCorner; // ��С����
    glm::vec3 m_maxCorner; // ��󶥵�
};
