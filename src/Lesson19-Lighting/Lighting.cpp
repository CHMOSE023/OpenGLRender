#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "iostream"
#include "../Entity/LightBox.h"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{
	// 1.准备数据
	virtual void Startup() 
	{		
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");

		m_triangle.Init();
		m_ground.Init();
		m_ground.SetTexture(m_textureGround);
		m_lightBox.Init();

	}

	// 2.渲染数据
	virtual void Render()
	{
		m_ground.Render(m_camera);	
		m_triangle.Render(m_camera);
		m_lightBox.Render(m_camera);
	}
	
	// 3.关闭
	virtual void Shutdown()
	{
		// 删除纹理
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: // 变量	

	// 模型类
	Ground    m_ground;   // 地面
	Triangle  m_triangle; // 三角形
	LightBox  m_lightBox;

	unsigned  m_textureCity   = 0;
	unsigned  m_textureGround = 0;	
	
};

int main()
{
	LighingApp lighingApp;	
	lighingApp.Initialize(1920 * 0.5, 1080 * 0.5, APPLICTION);
	lighingApp.Run();
}
