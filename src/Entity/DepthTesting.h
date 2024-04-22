#pragma once
#include "Entity.h"
#include "../Shader/ShaderDepthTesting.h"
class DepthTesting : public Entity
{
public :
	virtual void Init()  // ����׼��
	{
		glDepthFunc(GL_LESS);// ��Զͨ������
        m_shader.Initialize();

        float cubeVertices[] = {
            // ����               // uv
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };

        // ������ VAO        
        glGenVertexArrays(1, &m_cubeVao);
        glGenBuffers(1, &m_cubeVbo);
        glBindVertexArray(m_cubeVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_cubeVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(m_shader.m_position);
        glVertexAttribPointer(m_shader.m_position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(m_shader.m_uv);
        glVertexAttribPointer(m_shader.m_uv, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);
       
        // ���� VAO
        glGenVertexArrays(1, &m_planeVao);
        glGenBuffers(1, &m_planeVbo);
        glBindVertexArray(m_planeVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_planeVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(m_shader.m_position);
        glVertexAttribPointer(m_shader.m_position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(m_shader.m_uv);
        glVertexAttribPointer(m_shader.m_uv, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);

	}
	virtual void Render(const Camera& camera)
	{      
        glm::mat4 projectionMat = camera.GetProject();
        glm::mat4 viewMat       = camera.GetView();
        glm::mat4 modelMat      = glm::mat4(1.0f);


        m_shader.Begin();
        // ���ƺ���1
        glBindVertexArray(m_cubeVao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_cubeTexture);
        m_shader.SetFloat("texture1", 0);
        m_shader.SetMat4("view", viewMat);
        m_shader.SetMat4("projection", projectionMat);

       // modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_shader.SetMat4("model", modelMat);       
        glDrawArrays(GL_TRIANGLES,0,36);
        // ���ƺ���2
        modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.0f, 0.0f));
        m_shader.SetMat4("model", modelMat);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ���Ƶ���
        glBindVertexArray(m_planeVao);
        glBindTexture(GL_TEXTURE_2D, m_florTexture);
        m_shader.SetMat4("model", modelMat);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindVertexArray(0);

        m_shader.End();
		

	}

private:
    ShaderDepthTesting m_shader;
    unsigned m_cubeVao;
    unsigned m_cubeVbo;
    unsigned m_planeVao;
    unsigned m_planeVbo;
public:
    
    unsigned m_cubeTexture;
    unsigned m_florTexture;    


};