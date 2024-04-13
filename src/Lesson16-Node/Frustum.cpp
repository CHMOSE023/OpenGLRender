#include"Frustum.h"

// �жϵ��Ƿ�����׶���ڲ�
Frustum::Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
    // ������׶�������ƽ��
    glm::mat4 clipMatrix = projectionMatrix * viewMatrix;

    // ��ƽ��
    m_planes[0] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][0],
        clipMatrix[1][3] + clipMatrix[1][0],
        clipMatrix[2][3] + clipMatrix[2][0],
        clipMatrix[3][3] + clipMatrix[3][0]);
    // ��ƽ��
    m_planes[1] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][0],
        clipMatrix[1][3] - clipMatrix[1][0],
        clipMatrix[2][3] - clipMatrix[2][0],
        clipMatrix[3][3] - clipMatrix[3][0]);
    // ��ƽ��
    m_planes[2] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][1],
        clipMatrix[1][3] + clipMatrix[1][1],
        clipMatrix[2][3] + clipMatrix[2][1],
        clipMatrix[3][3] + clipMatrix[3][1]);
    // ��ƽ��
    m_planes[3] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][1],
        clipMatrix[1][3] - clipMatrix[1][1],
        clipMatrix[2][3] - clipMatrix[2][1],
        clipMatrix[3][3] - clipMatrix[3][1]);
    // ��ƽ��
    m_planes[4] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][2],
        clipMatrix[1][3] + clipMatrix[1][2],
        clipMatrix[2][3] + clipMatrix[2][2],
        clipMatrix[3][3] + clipMatrix[3][2]);
    // Զƽ��
    m_planes[5] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][2],
        clipMatrix[1][3] - clipMatrix[1][2],
        clipMatrix[2][3] - clipMatrix[2][2],
        clipMatrix[3][3] - clipMatrix[3][2]);

    // ��һ��ƽ��
    for (int i = 0; i < 6; ++i) {
        m_planes[i] /= glm::length(glm::vec3(m_planes[i]));
    }
}

bool Frustum::IsPointInside(const glm::vec3& point) const {
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(glm::vec3(m_planes[i]), point) + m_planes[i].w < 0) {
            return false; // ������׶���ⲿ
        }
    }
    return true; // ������׶���ڲ�
}

// �жϰ�Χ���Ƿ�����׶���ڲ�
bool Frustum::IsSphereInside(const glm::vec3& center, float radius) const {
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(glm::vec3(m_planes[i]), center) + m_planes[i].w < -radius) {
            return false; // ������׶��ƽ���ཻ
        }
    }
    return true; // ����ȫλ����׶���ڲ�
}

// �жϰ�Χ���Ƿ�����׶���ڲ�
bool Frustum::IsBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const {
    for (int i = 0; i < 6; ++i) {
        glm::vec3 p;
        p.x = (m_planes[i].x > 0) ? maxPoint.x : minPoint.x;
        p.y = (m_planes[i].y > 0) ? maxPoint.y : minPoint.y;
        p.z = (m_planes[i].z > 0) ? maxPoint.z : minPoint.z;

        if (glm::dot(glm::vec3(m_planes[i]), p) + m_planes[i].w < 0) {
            return false; // ��������׶��ƽ���ཻ
        }
    }
    return true; // ������ȫλ����׶���ڲ�
}
