#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Core/Camera.h"
#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{

	// 1.׼������
	virtual void Startup() 
	{		
		m_ground.Init();
		//m_camera.SetEye();
		
	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		glm::mat4 mat1(1);

		m_ground.Render(mat1);

	}
	// 3.�ر�
	virtual void Shutdown()
	{
		
	}

private: // ����

	Ground m_ground; // ����
	Camera m_camera;
};

int main()
{
	LighingApp lighingApp;
	lighingApp.Initialize(800,600, APPLICTION);
	lighingApp.Run();
}
