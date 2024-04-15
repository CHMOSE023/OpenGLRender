#pragma once
#include <glm/glm.hpp>
#include "Role.h"
#include "ThirdCamera.h"
#include "Shader_P3_C4_T2.h"
class Billboard
{
	struct  Vertex
	{
		glm::vec3  position;
		glm::vec2  uv;
		glm::vec4  color;
	};
public:
	Billboard() 
	{
	};
	~Billboard() 
	{
		// ��������
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	};
	void SetShader(Shader_P3_C4_T2 &shader)
	{
		m_shader = shader;
		glGenVertexArrays(1, &m_VAO); // ��������������� VAO	
		glGenBuffers(1, &m_VBO);      // �������㻺����� VBO	

	}

	
	void Render(const ThirdCamera& camera,const GLuint texture)
	{
		
		glm::vec3 faceDir = camera.GetRight();

		m_position = glm::vec3(1);
		m_size = glm::vec3(1);

		glm::vec3  lb = m_position - faceDir * m_size.x * 0.5f;
		glm::vec3  rb = m_position + faceDir * m_size.x * 0.5f;

		glm::vec3  lt = lb + glm::vec3(0, m_size.y, 0);
		glm::vec3  rt = rb + glm::vec3(0, m_size.y, 0);

		Vertex vert[6]
		{
			{   lb, glm::vec2(0,0),   glm::vec4(1)},
			{   rb, glm::vec2(1,0),   glm::vec4(1)},
			{   rt, glm::vec2(1,1),   glm::vec4(1)},
		
			{   lb, glm::vec2(0,0),   glm::vec4(1)},
			{   rt, glm::vec2(1,1),   glm::vec4(1)},
			{   lt, glm::vec2(0,1),   glm::vec4(1)}
		};

		glm::mat4  mvp(1);
		glm::mat4  matView = camera.GetView();
		glm::mat4  matProj = camera.GetProject();
		glm::mat4  matModel = glm::mat4x4(1.0);
		
		matModel = glm::scale(matModel, glm::vec3(5,5,5));

		mvp = matProj * matView * matModel;


		m_shader.Begin();

		glUniformMatrix4fv(m_shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);

		glBindTexture(GL_TEXTURE_2D, texture);// ʹ������2

		glBindVertexArray(m_VAO);               // �� VAO		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);   // �� VBO ���������
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);		
		glVertexAttribPointer(m_shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
		glEnableVertexAttribArray(m_shader.m_Position);
		glVertexAttribPointer(m_shader.m_UV, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
		glEnableVertexAttribArray(m_shader.m_UV);
		glVertexAttribPointer(m_shader.m_Color, 4, GL_FLOAT, false, sizeof(Vertex), (void*)20);
		glEnableVertexAttribArray(m_shader.m_Color);
		

		// ÿ�λ�֮ǰ��	
		//glBindVertexArray(m_VAO);     // �� VAO	
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_shader.End();
	}



public :

	glm::vec2     m_size;      // ��С
	glm::vec3     m_position;  // λ��
	glm::vec3     m_color;     // ��ɫ

	unsigned int  m_VBO;
	unsigned int  m_VAO;
	unsigned int  m_number;

	Shader_P3_C4_T2 m_shader;
	ThirdCamera     m_camera;
};

