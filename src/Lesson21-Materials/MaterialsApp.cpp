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
	std::vector <Entity*> entities;  // ģ������

	// 1.׼������
	virtual void Startup() 
	{	
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");

		// ����
		Ground* pGround = new Ground();
		pGround->Init();
		pGround->SetTexture(m_textureGround);
		entities.push_back(pGround);

		// ������
		Triangle* pTriangle = new Triangle();
		pTriangle->Init();
		entities.push_back(pTriangle);

		// ��ɫ����
		Box* pBox = new Box();
		pBox->Init();
		entities.push_back(pBox);

		// ����������
		BoxMaterials* pBoxMaterials = new BoxMaterials();
		pBoxMaterials->Init();
		entities.push_back(pBoxMaterials);
	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		// �ͷŶ�̬������ڴ�
		for (Entity* obj : entities) 
		{
			obj->Render(m_camera);
		}
	}
	
	// 3.�ر�
	virtual void Shutdown()
	{
		// �ͷŶ�̬������ڴ�
		for (Entity* obj : entities)
		{
			delete obj;
		}

		// ɾ������
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
