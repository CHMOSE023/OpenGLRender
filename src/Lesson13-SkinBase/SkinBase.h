#pragma once
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_interpolation.hpp>

/**
*   动画有一些列的帧组成，描述一帧数据的信息
*/
class   Frame
{
public:
    glm::mat4 m_Bone[2];
};


/**
*   描述一个骨骼动画
*/
class   SkinBase
{
public:
    void    CalcFrame(float t, Frame& frame) const
    {
        // interpolate 插值计算
        frame.m_Bone[0] = glm::interpolate(m_KeyFrame[0].m_Bone[0], m_KeyFrame[1].m_Bone[0], t);
        frame.m_Bone[1] = glm::interpolate(m_KeyFrame[0].m_Bone[1], m_KeyFrame[1].m_Bone[1], t);
    }
public:
    /**
    *   该动画有两帧数据
    */ 
    Frame   m_KeyFrame[2];
};
