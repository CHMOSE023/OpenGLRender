#include"Frustum.h"

// �жϵ��Ƿ�����׶���ڲ�
Frustum::Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
    // ������׶�������ƽ��
    glm::mat4 clipMatrix = projectionMatrix * viewMatrix;

    // ��ƽ��
    planes[0] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][0],
        clipMatrix[1][3] + clipMatrix[1][0],
        clipMatrix[2][3] + clipMatrix[2][0],
        clipMatrix[3][3] + clipMatrix[3][0]);
    // ��ƽ��
    planes[1] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][0],
        clipMatrix[1][3] - clipMatrix[1][0],
        clipMatrix[2][3] - clipMatrix[2][0],
        clipMatrix[3][3] - clipMatrix[3][0]);
    // ��ƽ��
    planes[2] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][1],
        clipMatrix[1][3] + clipMatrix[1][1],
        clipMatrix[2][3] + clipMatrix[2][1],
        clipMatrix[3][3] + clipMatrix[3][1]);
    // ��ƽ��
    planes[3] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][1],
        clipMatrix[1][3] - clipMatrix[1][1],
        clipMatrix[2][3] - clipMatrix[2][1],
        clipMatrix[3][3] - clipMatrix[3][1]);
    // ��ƽ��
    planes[4] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][2],
        clipMatrix[1][3] + clipMatrix[1][2],
        clipMatrix[2][3] + clipMatrix[2][2],
        clipMatrix[3][3] + clipMatrix[3][2]);
    // Զƽ��
    planes[5] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][2],
        clipMatrix[1][3] - clipMatrix[1][2],
        clipMatrix[2][3] - clipMatrix[2][2],
        clipMatrix[3][3] - clipMatrix[3][2]);

    // ��һ��ƽ��
    for (int i = 0; i < 6; ++i) {
        planes[i] /= glm::length(glm::vec3(planes[i]));
    }
}

bool Frustum::isPointInside(const glm::vec3& point) const {
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(glm::vec3(planes[i]), point) + planes[i].w < 0) {
            return false; // ������׶���ⲿ
        }
    }
    return true; // ������׶���ڲ�
}

// �жϰ�Χ���Ƿ�����׶���ڲ�
bool Frustum::isSphereInside(const glm::vec3& center, float radius) const {
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(glm::vec3(planes[i]), center) + planes[i].w < -radius) {
            return false; // ������׶��ƽ���ཻ
        }
    }
    return true; // ����ȫλ����׶���ڲ�
}

// �жϰ�Χ���Ƿ�����׶���ڲ�
bool Frustum::isBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const {
    for (int i = 0; i < 6; ++i) {
        glm::vec3 p;
        p.x = (planes[i].x > 0) ? maxPoint.x : minPoint.x;
        p.y = (planes[i].y > 0) ? maxPoint.y : minPoint.y;
        p.z = (planes[i].z > 0) ? maxPoint.z : minPoint.z;

        if (glm::dot(glm::vec3(planes[i]), p) + planes[i].w < 0) {
            return false; // ��������׶��ƽ���ཻ
        }
    }
    return true; // ������ȫλ����׶���ڲ�
}
