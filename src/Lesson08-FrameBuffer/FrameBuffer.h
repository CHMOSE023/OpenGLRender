#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class   FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();
public:
 
    void    Create(int width, int height); // 创建一个缓冲区对象  
    void    Begin(unsigned texId);         // 使用对象  
    void    End();                         // 使用完，回复状态
public:
    unsigned    m_Width;
    unsigned    m_Height;
    unsigned    m_FBOID;
    unsigned    m_DEPTHID;
};