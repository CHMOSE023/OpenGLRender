#include "Application.h"
#include "Application.h"

#pragma region glfw窗口及事件处理
Application::Application()
{
}

Application::~Application()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::Initialize(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGL();
	glfwSwapInterval(1);     // 垂直同步打开1 关闭0	
	glEnable(GL_DEPTH_TEST); // 开启深度测试
}

void Application::Run()
{
	Startup();    // 1.渲染前准备工作
	double curTime = 0;  // 帧类用时
	int    framesNumber = 0;  // 

	while (!glfwWindowShouldClose(m_pWindow))
	{
		double   elapseTime = (double)m_timeStamp.GetElapsedSecond();
		m_elapsedTime += elapseTime;               // 累计用时			
		curTime += m_timeStamp.GetElapsedSecond(); // 计算帧率
		if (curTime >= 1.0f)
		{
			m_franerNuber = framesNumber;			
			framesNumber = 0;
			curTime = 0;	
		}
		else
		{
			framesNumber++;
		}

		m_timeStamp.Update();

		glfwGetFramebufferSize(m_pWindow, &m_winWidth, &m_winHeight);

		glViewport(0, 0, m_winWidth, m_winHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		Render(); // 2.开始渲染

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents(); // 检查窗口当前是否有事件发生		
	}
	Shutdown();   // 3.结束渲染
}
#pragma endregion 

void Application::Startup()
{
}

void Application::Render()
{
}

void Application::Shutdown()
{
	
}
