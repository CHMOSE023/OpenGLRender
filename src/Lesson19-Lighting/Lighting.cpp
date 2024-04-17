#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "iostream"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{
	// 1.准备数据
	virtual void Startup() 
	{		
		m_ground.Init();
		m_triangle.Init();	
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");


	}

	// 2.渲染数据
	virtual void Render()
	{
		m_ground.Render(m_camera, m_textureGround);	

		m_triangle.Render(m_camera);
		DrawtTiangle();
	}
	

	// 绘制三角形
	void DrawtTiangle()
	{
	

		//std::cout << glm::to_string(mvp) << std::endl;		
		
	}

	// 3.关闭
	virtual void Shutdown()
	{
		// 删除纹理
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: // 变量	
	Ground    m_ground;   // 地面
	Triangle  m_triangle; // 三角形


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
