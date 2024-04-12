#include "Role.h"
#include <glm/glm.hpp>
Role::Role()
{
    m_Position = glm::vec3(0); // λ��
    m_Target   = glm::vec3(0); // Ŀ��
    m_Speed    = 5;
}

Role::~Role() {}

void Role::SetTarget(glm::vec3 target)
{
    m_Target = target;
}

// ����λ��
void Role::SetPosition(glm::vec3 pos)
{
    m_Position = pos;
    m_Position.y = 1;
}

//
void Role::MoveCheck(const float elasped)
{
    //  Ŀ��λ�ò��ǵ�ǰλ�á�
    if (m_Target == m_Position)
    {
        return;
    }

    // ��ȡ��ǰ���λ����Ŀ��λ�õ�ƫ����
    glm::vec3   offset = m_Target - m_Position;

    // ��ȡ���ƶ��ķ���
    glm::vec3  dir = glm::normalize(offset);

    // ������������֮��ľ���
    if (glm::distance(m_Target, m_Position) > 1)
    {
        float   speed = elasped * m_Speed;
        m_Position += glm::vec3(dir.x * speed, 0, dir.z * speed);
    }
    else
    {
        m_Target = m_Position;
    }
}

// ���ƽ�ɫ
void Role::Render(float fElapsed, ThirdCamera& camera, Shader_P3_C4_T2& shader, GLuint texture, GLuint vertexArray, int size)
{
    MoveCheck(fElapsed);

    float     angle = glfwGetTime();
    glm::vec3  axis(0.0f, 1.0f, 0.0f); // ��ת��

    glm::mat4  matModel(1);  
    matModel = glm::translate(matModel,m_Position);
    matModel = glm::translate(matModel, glm::vec3(0, 10.0, 0));
    matModel = glm::scale(matModel,glm::vec3(5.0,5.0,5.0));

    glm::mat4  matProj  = camera.GetProject();
    glm::mat4  matView  = camera.GetView(); 
               matModel = glm::rotate(matModel, angle, axis);

    glm::mat4  mvp      = matProj * matView * matModel;

    shader.Begin();   
      glBindTexture(GL_TEXTURE_2D, texture);
      glBindVertexArray(vertexArray);
      glUniformMatrix4fv(shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);
      glDrawArrays(GL_TRIANGLES, 0, size);   
    shader.End();
}

