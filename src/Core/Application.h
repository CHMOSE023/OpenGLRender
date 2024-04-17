#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TimeStamp.h"
class Application
{
public:
	Application();
	virtual ~Application();
	virtual void Initialize(int width, int height, const char* title);  // 1.初始化
	virtual void Run();
private:
	virtual void Startup();         // 1.准备数据
	virtual void Render();          // 2.渲染数据
	virtual void Shutdown();        // 3.关闭

public:
	int           m_winWidth;
	int	          m_winHeight;
	GLFWwindow*   m_pWindow;	
	TimeStamp     m_timeStamp;     // 时间戳

	double        m_elapsedTime;   // 经过时长
	double        m_frameTime;     // 记录上一帧的时间	,一次SwapBuffers用时		
	unsigned int  m_franerNuber;   // 帧数
	double        m_xPos;		   // 鼠标x
	double        m_yPos;		   // 鼠标y
	
};

