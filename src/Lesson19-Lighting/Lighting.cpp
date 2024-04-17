#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "iostream"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{
	// 1.׼������
	virtual void Startup() 
	{		
		m_ground.Init();
		m_triangle.Init();	
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");


	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		m_ground.Render(m_camera, m_textureGround);	

		m_triangle.Render(m_camera);
		DrawtTiangle();
	}
	

	// ����������
	void DrawtTiangle()
	{
	

		//std::cout << glm::to_string(mvp) << std::endl;		
		
	}

	// 3.�ر�
	virtual void Shutdown()
	{
		// ɾ������
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: // ����	
	Ground    m_ground;   // ����
	Triangle  m_triangle; // ������


	unsigned        m_vao = 0;;
	unsigned        m_vbo = 0;;
	Shader_P3_C4_T2 m_shader;

	unsigned  m_textureCity   = 0;
	unsigned  m_textureGround = 0;	
	
};

int main()
{
	LighingApp lighingApp;	
	lighingApp.Initialize(800,600, APPLICTION);
	lighingApp.Run();
}
