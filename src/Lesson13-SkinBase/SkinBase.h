#pragma once
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_interpolation.hpp>

/**
*   ������һЩ�е�֡��ɣ�����һ֡���ݵ���Ϣ
*/
class   Frame
{
public:
    glm::mat4 m_Bone[2];
};


/**
*   ����һ����������
*/
class   SkinBase
{
public:
    void    CalcFrame(float t, Frame& frame) const
    {
        // interpolate ��ֵ����
        frame.m_Bone[0] = glm::interpolate(m_KeyFrame[0].m_Bone[0], m_KeyFrame[1].m_Bone[0], t);
        frame.m_Bone[1] = glm::interpolate(m_KeyFrame[0].m_Bone[1], m_KeyFrame[1].m_Bone[1], t);
    }
public:
    /**
    *   �ö�������֡����
    */ 
    Frame   m_KeyFrame[2];
};
