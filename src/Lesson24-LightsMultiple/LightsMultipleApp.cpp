#include "../Core/Application.h"
#include "../Entity/BoxLightsMultiple.h"
class LightsMultipleApp :public Application
{
public:	
	// 1.׼������
	virtual void  Startup()
	{
		//printf("1.׼������\r\n");
		boxMultipleLights.Init();
		boxMultipleLights.m_diffuseMap  = CreateTexture("textures/container2.png");
		boxMultipleLights.m_specularMap = CreateTexture("textures/container2_specular.png");

	}; 
	// 2.��Ⱦ����
	virtual void  Render() 
	{
		
		boxMultipleLights.Render(m_camera);

	};
	// 3.�ر�
	virtual void  Shutdown()
	{
	

	};

private:
	BoxLightsMultiple boxMultipleLights;


};



int main()
{
	LightsMultipleApp app;
	app.Initialize(800,600,"Lesson24-MultipleLights");
	app.Run();
}