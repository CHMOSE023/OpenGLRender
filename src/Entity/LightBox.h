#include "Entity.h"
#include "../Shader/LightingDiffuse.h"
#include "../Shader/Shader_P3.h"
#include "../Core/Camera.h"
#include <glm/gtc/type_ptr.hpp>

class LightBox :public Entity
{
public:
    LightBox()
	{
        m_vaoCube  = -1;
        m_vaoLight = -1;
        m_vbo      = -1;
	};
	~LightBox()
	{
		glDeleteVertexArrays(1, &m_vaoCube);
		glDeleteVertexArrays(1, &m_vaoLight);
		glDeleteBuffers(1, &m_vbo);

	};
	virtual void Init()
	{
        float vertices[] = {
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        m_lightingShader.Initialize();
        m_lightCubeShader.Initialize();
        
        glGenVertexArrays(1, &m_vaoCube);
        glGenBuffers(1, &m_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_vaoCube);

        // 设置顶点属性
        glVertexAttribPointer    (m_lightingShader.m_position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(m_lightingShader.m_position);
        glVertexAttribPointer    (m_lightingShader.m_normal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(m_lightingShader.m_normal);

        // 绘制灯光模型
        glGenVertexArrays(1, &m_vaoLight);
        glBindVertexArray(m_vaoLight);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer    (m_lightCubeShader.m_position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(m_lightCubeShader.m_position);

	}

	virtual void  Render(const Camera &camera )
	{

        // glm::mat4 model(1.0f);
        // glm::mat4 view       = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)900 / (GLfloat)600, 0.1f, 100.0f);

        // glUniformMatrix4fv(m_lightingShader.m_model, 1, GL_FALSE, glm::value_ptr(model));
        // glUniformMatrix4fv(m_lightingShader.m_view, 1, GL_FALSE,  glm::value_ptr(view));
        // glUniformMatrix4fv(m_lightingShader.m_proj, 1, GL_FALSE,  glm::value_ptr(projection));


        // 绘制盒子
        m_lightCubeShader.Begin();
        glm::mat4 model(1);
        glUniformMatrix4fv(m_lightingShader.m_model, 1, GL_FALSE, (const GLfloat*)&model);
        glUniformMatrix4fv(m_lightingShader.m_view,  1, GL_FALSE, (const GLfloat*)&camera.GetView());
        glUniformMatrix4fv(m_lightingShader.m_proj,  1, GL_FALSE, (const GLfloat*)&camera.GetProject());  

        glUniform3f(m_lightingShader.m_objectColor,1.0f,0.5f,0.31f);
        glUniform3f(m_lightingShader.m_lightColor, 1.0f, 1.0f, 1.0f);
        glUniform3f(m_lightingShader.m_lightPos,   1.2f, 1.0f, 2.0f);

    
        glBindVertexArray(m_vaoCube);

        glDrawArrays(GL_TRIANGLES, 0, 36);
      

        m_lightCubeShader.End();


        // 绘制灯光位置
        m_lightingShader.Begin();

        glUniformMatrix4fv(m_lightCubeShader.m_view, 1, GL_FALSE, (const GLfloat*)&camera.GetView());
        glUniformMatrix4fv(m_lightCubeShader.m_proj, 1, GL_FALSE, (const GLfloat*)&camera.GetProject());

        model = glm::mat4(1);

        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(m_lightCubeShader.m_model, 1, GL_FALSE, (const GLfloat*)&model);


        glBindVertexArray(m_vaoLight);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        m_lightingShader.End();

	};


private:
	unsigned  m_vaoCube;
	unsigned  m_vaoLight;
	unsigned  m_vbo;
	
    Shader_P3       m_lightCubeShader;
    LightingDiffuse m_lightingShader;
    

};
