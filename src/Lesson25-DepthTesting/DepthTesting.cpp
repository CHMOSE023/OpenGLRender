#include "../Core/Application.h"
#include "../Entity/DepthTesting.h"
class DepthTestingApp:public Application
{
public:

	// 1.׼������
	virtual void  Startup() 
	{
		m_depthTesting.Init();
	
		// ��������
		m_depthTesting.m_cubeTexture = CreateTexture("textures/marble.jpg");
		// ��������
		m_depthTesting.m_florTexture = CreateTexture("textures/metal.png");



	}

	// 2.��Ⱦ����
	virtual void  Render()         
	{
		m_depthTesting.Render(m_camera);
	}

	// 3.�ر�
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