#include "AABB.h"

// ���캯��
AABB::AABB() 
    : m_minCorner(glm::vec3(std::numeric_limits<float>::max()))
    , m_maxCorner(glm::vec3(std::numeric_limits<float>::lowest()))
{
}

AABB::AABB(const glm::vec3& min, const glm::vec3& max) 
    : m_minCorner(min)
    , m_maxCorner(max) 
{
}

// ��ȡ��С��������

glm::vec3 AABB::GetMinCorner() const 
{ 
    return m_minCorner; 
}

// ��ȡ��󶥵�����

glm::vec3 AABB::GetMaxCorner() const 
{ 
    return m_maxCorner;
}

// ��ȡ��Χ�е����ĵ�

glm::vec3 AABB::GetCenter() const 
{
    return (m_minCorner + m_maxCorner) * 0.5f;
}

// ��ȡ��Χ�еĳߴ�

glm::vec3 AABB::GetSize() const 
{
    return m_maxCorner - m_minCorner;
}

// �����Χ�е����

float AABB::GetVolume() const 
{
    glm::vec3 size = GetSize();
    return size.x * size.y * size.z;
}

// �����Χ�еı����

float AABB::GetSurfaceArea() const 
{
    glm::vec3 size = GetSize();
    return 2.0f * (size.x * size.y + size.x * size.z + size.y * size.z);
}

// �����Ƿ��ڰ�Χ����

bool AABB::Contains(const glm::vec3& point) const 
{
    return (point.x >= m_minCorner.x && point.x <= m_maxCorner.x &&
        point.y >= m_minCorner.y && point.y <= m_maxCorner.y &&
        point.z >= m_minCorner.z && point.z <= m_maxCorner.z);
}

// �ϲ�������Χ�У������µİ�Χ��

AABB AABB::Merge(const AABB& other) const 
{
    glm::vec3 newMin = glm::min(m_minCorner, other.m_minCorner);
    glm::vec3 newMax = glm::max(m_maxCorner, other.m_maxCorner);
    return AABB(newMin, newMax);
}

// ���������Χ���Ƿ��ཻ

bool AABB::Intersects(const AABB& other) const 
{
    return (m_minCorner.x <= other.m_maxCorner.x && m_maxCorner.x >= other.m_minCorner.x) &&
        (m_minCorner.y <= other.m_maxCorner.y && m_maxCorner.y >= other.m_minCorner.y) &&
        (m_minCorner.z <= other.m_maxCorner.z && m_maxCorner.z >= other.m_minCorner.z);
}

// ��Χ�б任

void AABB::Transform(const glm::mat4& matrix)
{
    glm::vec4 corners[8];
    corners[0] = matrix * glm::vec4(m_minCorner.x, m_minCorner.y, m_minCorner.z, 1.0f);
    corners[1] = matrix * glm::vec4(m_maxCorner.x, m_minCorner.y, m_minCorner.z, 1.0f);
    corners[2] = matrix * glm::vec4(m_maxCorner.x, m_maxCorner.y, m_minCorner.z, 1.0f);
    corners[3] = matrix * glm::vec4(m_minCorner.x, m_maxCorner.y, m_minCorner.z, 1.0f);
    corners[4] = matrix * glm::vec4(m_minCorner.x, m_minCorner.y, m_maxCorner.z, 1.0f);
    corners[5] = matrix * glm::vec4(m_maxCorner.x, m_minCorner.y, m_maxCorner.z, 1.0f);
    corners[6] = matrix * glm::vec4(m_maxCorner.x, m_maxCorner.y, m_maxCorner.z, 1.0f);
    corners[7] = matrix * glm::vec4(m_minCorner.x, m_maxCorner.y, m_maxCorner.z, 1.0f);

    m_minCorner = m_maxCorner = glm::vec3(corners[0]);
    for (int i = 1; i < 8; ++i) {
        m_minCorner = glm::min(m_minCorner, glm::vec3(corners[i]));
        m_maxCorner = glm::max(m_maxCorner, glm::vec3(corners[i]));
    }
}

// �ӵ������ɰ�Χ��

AABB AABB::FromPointCloud(const std::vector<glm::vec3>& points)
{
    if (points.empty())
    {
        return AABB();
    }

    glm::vec3 minPoint = *std::min_element(points.begin(), points.end(), [](const glm::vec3& a, const glm::vec3& b)
        {
            return a.x < b.x;
        });
    glm::vec3 maxPoint = *std::max_element(points.begin(), points.end(), [](const glm::vec3& a, const glm::vec3& b)
        {
            return a.x < b.x;
        });

    for (const auto& point : points)
    {
        minPoint = glm::min(minPoint, point);
        maxPoint = glm::max(maxPoint, point);
    }

    return AABB(minPoint, maxPoint);
}
