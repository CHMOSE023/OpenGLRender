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
	virtual void Initialize(int width, int height, const char* title);  // 1.��ʼ��
	virtual void Run();
private:
	virtual void Startup();         // 1.׼������
	virtual void Render();          // 2.��Ⱦ����
	virtual void Shutdown();        // 3.�ر�

public:
	int           m_winWidth;
	int	          m_winHeight;
	GLFWwindow*   m_pWindow;	
	TimeStamp     m_timeStamp;     // ʱ���

	double        m_elapsedTime;   // ����ʱ��
	double        m_frameTime;     // ��¼��һ֡��ʱ��	,һ��SwapBuffers��ʱ		
	unsigned int  m_franerNuber;   // ֡��
	double        m_xPos;		   // ���x
	double        m_yPos;		   // ���y
	
};

