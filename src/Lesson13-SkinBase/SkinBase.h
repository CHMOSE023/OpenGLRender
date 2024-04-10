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
    glm::mat4 _bone[2];
};


/**
*   描述一个骨骼动画
*/
class   SkinAnimation
{
public:
    void    calcFrame(float t, Frame& frame)
    {
        // interpolate 插值计算
        frame._bone[0] = glm::interpolate(_keyFrame[0]._bone[0], _keyFrame[1]._bone[0], t);
        frame._bone[1] = glm::interpolate(_keyFrame[0]._bone[1], _keyFrame[1]._bone[1], t);

    }
public:
    /**
    *   该动画有两帧数据
    */
    Frame   _keyFrame[2];
};
