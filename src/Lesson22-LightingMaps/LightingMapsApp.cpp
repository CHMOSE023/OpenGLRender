#include "../Core/Application.h"
#include "../Entity/Entity.h"
#include <vector>
#include "../Entity/Ground.h"

class LightingMapsApp :public Application
{
public:
	LightingMapsApp() {};
	~LightingMapsApp() {};

	
	// 1.׼������
	virtual void Startup()
	{
		// ׼����������
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");

		// ����
		Ground* pGround = new Ground();
		pGround->Init();
		pGround->SetTexture(m_textureGround);
		entities.push_back(pGround);
	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		// ������Ⱦģ��
		for (Entity* obj:entities )
		{
			obj->Render(m_camera);
		}
		
	}
	
	// 3.�ر�
	virtual void Shutdown()
	{
		// ����
		for (Entity *obj :entities)
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

};



int main()
{
	LightingMapsApp app;
	app.Initialize(800,600,"Lesson22-LightingMaps");
	app.Run();

}