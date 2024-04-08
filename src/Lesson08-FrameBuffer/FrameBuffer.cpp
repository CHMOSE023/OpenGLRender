#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    m_Width = 0;
    m_Height = 0;
    m_FBOID = 0;
    m_DEPTHID = 0;
}
FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_FBOID);
    glDeleteRenderbuffers(1, &m_DEPTHID);
}


void FrameBuffer::Create(int width, int height)
{
    m_Width = width;
    m_Height = height;

    // 生成帧缓冲对象名称
    glGenFramebuffers(1, &m_FBOID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBOID);

    // 生成渲染缓冲对象名称
    glGenRenderbuffers(1, &m_DEPTHID);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DEPTHID);
    
    // 为渲染缓冲对象分配存储空间
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);
    // 将渲染缓冲对象附加到帧缓冲对象的特定附件上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DEPTHID);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Begin(unsigned texId)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBOID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
}

void FrameBuffer::End()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
