#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "iostream"
#include "../Entity/Box.h"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{
	// 1.׼������
	virtual void Startup() 
	{		
		m_textureCity = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");

		m_triangle.Init();
		m_ground.Init();
		m_ground.SetTexture(m_textureGround);

	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		m_ground.Render(m_camera);	
		m_triangle.Render(m_camera);		
	}
	
	// 3.�ر�
	virtual void Shutdown()
	{
		// ɾ������
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: // ����	

	// ģ����
	Ground    m_ground;   // ����
	Triangle  m_triangle; // ������
	Box       m_box;


	unsigned        m_vao = 0;;
	unsigned        m_vbo = 0;;
	Shader_P3_C4_T2 m_shader;

	unsigned  m_textureCity   = 0;
	unsigned  m_textureGround = 0;	
	
};

int main()
{
	LighingApp lighingApp;	
	lighingApp.Initialize(1920 * 0.5, 1080 * 0.5, APPLICTION);
	lighingApp.Run();
}
