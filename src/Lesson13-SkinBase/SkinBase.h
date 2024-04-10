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
    glm::mat4 _bone[2];
};


/**
*   ����һ����������
*/
class   SkinAnimation
{
public:
    void    calcFrame(float t, Frame& frame)
    {
        // interpolate ��ֵ����
        frame._bone[0] = glm::interpolate(_keyFrame[0]._bone[0], _keyFrame[1]._bone[0], t);
        frame._bone[1] = glm::interpolate(_keyFrame[0]._bone[1], _keyFrame[1]._bone[1], t);

    }
public:
    /**
    *   �ö�������֡����
    */
    Frame   _keyFrame[2];
};
