#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "../Entity/Box.h"
#include "../Entity/BoxMaterials.h"
#include "../Shader/ShaderCube.h"
#include <iostream>
#include <vector>

constexpr auto APPLICTION = "Lesson21-Materials";

class MaterialsAPP :public Application
{	
	std::vector <Entity*> entities;  // 模型数组

	// 1.准备数据
	virtual void Startup() 
	{	
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");

		// 地面
		Ground* pGround = new Ground();
		pGround->Init();
		pGround->SetTexture(m_textureGround);
		entities.push_back(pGround);

		// 三角形
		Triangle* pTriangle = new Triangle();
		pTriangle->Init();
		entities.push_back(pTriangle);

		// 彩色盒子
		Box* pBox = new Box();
		pBox->Init();
		entities.push_back(pBox);

		// 材质立方体
		BoxMaterials* pBoxMaterials = new BoxMaterials();
		pBoxMaterials->Init();
		entities.push_back(pBoxMaterials);
	}

	// 2.渲染数据
	virtual void Render()
	{
		// 释放动态分配的内存
		for (Entity* obj : entities) 
		{
			obj->Render(m_camera);
		}
	}
	
	// 3.关闭
	virtual void Shutdown()
	{
		// 释放动态分配的内存
		for (Entity* obj : entities)
		{
			delete obj;
		}

		// 删除纹理
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: 

	unsigned  m_textureCity   = 0;
	unsigned  m_textureGround = 0;	
	
};

int main()
{
	MaterialsAPP app;
	app.Initialize(1920 * 0.5, 1080 * 0.5, APPLICTION);
	app.Run();
}
