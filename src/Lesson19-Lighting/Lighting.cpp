#include"../Core/Application.h"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{

	// 1.׼������
	virtual void Startup() 
	{
		printf("1.׼������\n");
	}

	// 2.��Ⱦ����
	virtual void Render()
	{
		printf("2.��Ⱦ֡��: %d\n" ,m_franerNuber);
	}
	// 3.�ر�
	virtual void Shutdown()
	{
		printf("3.�ر�\n");
	}

private: 	// ����

};

int main()
{
	LighingApp lighingApp;
	lighingApp.Initialize(800,600, APPLICTION);
	lighingApp.Run();
}
