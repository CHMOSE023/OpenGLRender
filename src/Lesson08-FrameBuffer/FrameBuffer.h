#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class   FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();
public:
 
    void    Create(int width, int height); // ����һ������������  
    void    Begin(unsigned texId);         // ʹ�ö���  
    void    End();                         // ʹ���꣬�ظ�״̬
public:
    unsigned    m_Width;
    unsigned    m_Height;
    unsigned    m_FBOID;
    unsigned    m_DEPTHID;
};