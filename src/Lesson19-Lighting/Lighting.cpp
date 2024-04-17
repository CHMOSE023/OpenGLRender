#include"../Core/Application.h"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{

	// 1.准备数据
	virtual void Startup() 
	{
		printf("1.准备数据\n");
	}

	// 2.渲染数据
	virtual void Render()
	{
		printf("2.渲染帧率: %d\n" ,m_franerNuber);
	}
	// 3.关闭
	virtual void Shutdown()
	{
		printf("3.关闭\n");
	}

private: 	// 变量

};

int main()
{
	LighingApp lighingApp;
	lighingApp.Initialize(800,600, APPLICTION);
	lighingApp.Run();
}
