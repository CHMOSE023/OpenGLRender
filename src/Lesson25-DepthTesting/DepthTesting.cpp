#include "../Core/Application.h"
#include "../Entity/DepthTesting.h"
class DepthTestingApp:public Application
{
public:

	// 1.准备数据
	virtual void  Startup() 
	{
		m_depthTesting.Init();
	
		// 盒子纹理
		m_depthTesting.m_cubeTexture = CreateTexture("textures/marble.jpg");
		// 地面纹理
		m_depthTesting.m_florTexture = CreateTexture("textures/metal.png");



	}

	// 2.渲染数据
	virtual void  Render()         
	{
		m_depthTesting.Render(m_camera);
	}

	// 3.关闭
	virtual void  Shutdown()      
	{

	}
	DepthTesting m_depthTesting;

};


int main()
{
	DepthTestingApp app;
	app.Initialize(800,600,"lesson25-DepthTestingApp");
	app.Run();
}