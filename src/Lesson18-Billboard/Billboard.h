#pragma once
#include <glm/glm.hpp>
#include "Role.h"
#include "ThirdCamera.h"
#include "Shader_P3_C4_T2.h"
#define PI 3.1415926
class Billboard
{
	struct  Vertex
	{
		glm::vec3  position;
		glm::vec2  uv;
		glm::vec4  color;
	};
public:
	static  float   UnitRandom()
	{
		return float(rand()) / float(RAND_MAX);
	}

	static  float   RangeRandom(float fLow, float fHigh)
	{
		return (fHigh - fLow) * UnitRandom() + fLow;
	}
	Billboard() 
	{
		m_xinc = float(PI * 0.3);
		m_zinc = float(PI * 0.44);
		m_xpos = RangeRandom(-float(PI), float(PI));
		m_zpos = RangeRandom(-float(PI), float(PI));
	};
	~Billboard() 
	{
		// 清理数据
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	};
	void SetShader(Shader_P3_C4_T2 &shader)
	{
		m_shader = shader;
		glGenVertexArrays(1, &m_VAO); // 创建顶点数组对象 VAO	
		glGenBuffers(1, &m_VBO);      // 创建顶点缓冲对象 VBO	

	}

	
	void Render(const ThirdCamera& camera,const GLuint texture)
	{
		
		glm::vec3 faceDir = camera.GetRight();

		m_position = glm::vec3(1);
		m_size = glm::vec3(1);

		glm::vec3  lb = m_position - faceDir * m_size.x * 0.5f;
		glm::vec3  rb = m_position + faceDir * m_size.x * 0.5f;

		glm::vec3  lt = lb + glm::vec3(0, m_size.y, 0) ;
		glm::vec3  rt = rb + glm::vec3(0, m_size.y, 0) ;

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

		glBindTexture(GL_TEXTURE_2D, texture);// 使用纹理2

		glBindVertexArray(m_VAO);               // 绑定 VAO		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);   // 绑定 VBO 并填充数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);		
		glVertexAttribPointer(m_shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
		glEnableVertexAttribArray(m_shader.m_Position);
		glVertexAttribPointer(m_shader.m_UV, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
		glEnableVertexAttribArray(m_shader.m_UV);
		glVertexAttribPointer(m_shader.m_Color, 4, GL_FLOAT, false, sizeof(Vertex), (void*)20);
		glEnableVertexAttribArray(m_shader.m_Color);
		

		// 每次会之前绑定	
		//glBindVertexArray(m_VAO);     // 绑定 VAO	
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_shader.End();
	}



	void Render(float deltaTime,const ThirdCamera& camera, const GLuint texture)
	{

		m_xpos += m_xinc * deltaTime;
		m_zpos += m_zinc * deltaTime;

		glm::vec3  offset(0);
		offset.x = sin(m_xpos);
		offset.z = sin(m_zpos);

		glm::vec3 faceDir = camera.GetRight();

		m_position = glm::vec3(1);
		m_size = glm::vec3(1);

		glm::vec3  lb = m_position - faceDir * m_size.x * 0.5f;
		glm::vec3  rb = m_position + faceDir * m_size.x * 0.5f;

		glm::vec3  lt = lb + glm::vec3(0, m_size.y, 0) + offset;
		glm::vec3  rt = rb + glm::vec3(0, m_size.y, 0) + offset;

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
		matModel = glm::translate(matModel, glm::vec3(10, 0, 0));
		matModel = glm::scale(matModel, glm::vec3(5, 5, 5));

		mvp = matProj * matView * matModel;


		m_shader.Begin();

		glUniformMatrix4fv(m_shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);

		glBindTexture(GL_TEXTURE_2D, texture);// 使用纹理2

		glBindVertexArray(m_VAO);               // 绑定 VAO		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);   // 绑定 VBO 并填充数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
		glVertexAttribPointer(m_shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
		glEnableVertexAttribArray(m_shader.m_Position);
		glVertexAttribPointer(m_shader.m_UV, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
		glEnableVertexAttribArray(m_shader.m_UV);
		glVertexAttribPointer(m_shader.m_Color, 4, GL_FLOAT, false, sizeof(Vertex), (void*)20);
		glEnableVertexAttribArray(m_shader.m_Color);


		// 每次会之前绑定	
		//glBindVertexArray(m_VAO);     // 绑定 VAO	

		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_shader.End();
	}



public :

	glm::vec2     m_size;      // 大小
	glm::vec3     m_position;  // 位置
	glm::vec3     m_color;     // 颜色

	unsigned int  m_VBO;
	unsigned int  m_VAO;
	unsigned int  m_number;

	Shader_P3_C4_T2 m_shader;
	ThirdCamera     m_camera;

	/// 动画信息
	float       m_xinc;
	float       m_zinc;
	float       m_xpos;
	float       m_zpos;
};

