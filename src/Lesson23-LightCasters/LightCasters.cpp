#include "../Core/Application.h"
#include "../Entity/Entity.h"
#include "../Entity/Ground.h"
#include "../Entity/BoxLightingCastersDirectional.h"
#include <vector>

class LightingMapsApp :public Application
{
public:
	LightingMapsApp() {};
	~LightingMapsApp()
	{

	};

	// 1.׼������
	virtual void Startup()
	{
		// ׼����������
		m_textureCity = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");
		m_diffuseMap = CreateTexture("textures/container2.png");
		m_specularMap = CreateTexture("textures/container2_specular.png");

		// ����
		Ground* pGround = new Ground();
		pGround->Init();
		pGround->SetTexture(m_textureGround);
		entities.push_back(pGround);

		BoxLightingCastersDirectional* pBoxLightingCastersDirectional = new BoxLightingCastersDirectional;
		// �����������
		pBoxLightingCastersDirectional->m_diffuseMap = m_diffuseMap;
		pBoxLightingCastersDirectional->m_specularMap = m_specularMap;

		pBoxLightingCastersDirectional->Init();

		entities.push_back(pBoxLightingCastersDirectional);
	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		// ������Ⱦģ��
		for (Entity* obj : entities)
		{
			obj->Render(m_camera);
		}
	}

	// 3.�ر�
	virtual void Shutdown()
	{
		// ����
		for (Entity* obj : entities)
		{
			delete obj;
		}

		// ɾ������
		glDeleteTextures(1, &m_textureCity);
		glDeleteTextures(1, &m_textureGround);

	}

private:
	std::vector <Entity*> entities;  // ģ������
	unsigned  m_textureCity = 0;
	unsigned  m_textureGround = 0;
	unsigned  m_diffuseMap = 0;
	unsigned  m_specularMap = 0;
};


int main()
{
	LightingMapsApp app;
	app.Initialize(800, 600, "Lesson23-LightCasters");
	app.Run();

}