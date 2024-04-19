
#include "../Core/Application.h"
#include "../Entity/Entity.h"
#include <vector>
#include "../Entity/Ground.h"
#include "../Entity/BoxLightingMaps.h"

class LightingMapsApp :public Application
{
public:
	LightingMapsApp() {};
	~LightingMapsApp() 
	{

	};
		
	// 1.准备数据
	virtual void Startup()
	{
		// 准备纹理数据
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");
		m_diffuseMap    = CreateTexture("textures/container2.png");
		m_specularMap   = CreateTexture("textures/container2_specular.png");

		// 地面
		Ground* pGround = new Ground();
		pGround->Init();
		pGround->SetTexture(m_textureGround);
		entities.push_back(pGround);

		BoxLightingMaps* pBoxLightingMaps =new BoxLightingMaps;
		// 创建纹理材质
		pBoxLightingMaps->m_diffuseMap  = m_diffuseMap;
		pBoxLightingMaps->m_specularMap = m_specularMap;

		pBoxLightingMaps->Init();

		entities.push_back(pBoxLightingMaps);
	}

	// 2.渲染数据
	virtual void Render()
	{
		// 遍历渲染模型
		for (Entity* obj:entities )
		{
			obj->Render(m_camera);
		}		
	}
	
	// 3.关闭
	virtual void Shutdown()
	{
		// 清理
		for (Entity *obj :entities)
		{
			delete obj;
		}

		// 删除纹理
		glDeleteTextures(1, &m_textureCity);
		glDeleteTextures(1, &m_textureGround);

	}
	
private:
	std::vector <Entity*> entities;  // 模型数组
	unsigned  m_textureCity = 0;
	unsigned  m_textureGround = 0;
	unsigned  m_diffuseMap = 0;
	unsigned  m_specularMap = 0;
	

};


int main()
{
	LightingMapsApp app;
	app.Initialize(800,600,"Lesson22-LightingMaps");
	app.Run();

}