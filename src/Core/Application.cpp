#include "Application.h"
#include "Application.h"

#pragma region glfw���ڼ��¼�����
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
	glfwSwapInterval(1);     // ��ֱͬ����1 �ر�0	
	glEnable(GL_DEPTH_TEST); // ������Ȳ���
}

void Application::Run()
{
	Startup();    // 1.��Ⱦǰ׼������
	double curTime = 0;  // ֡����ʱ
	int    framesNumber = 0;  // 

	while (!glfwWindowShouldClose(m_pWindow))
	{
		double   elapseTime = (double)m_timeStamp.GetElapsedSecond();
		m_elapsedTime += elapseTime;               // �ۼ���ʱ			
		curTime += m_timeStamp.GetElapsedSecond(); // ����֡��
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

		Render(); // 2.��ʼ��Ⱦ

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents(); // ��鴰�ڵ�ǰ�Ƿ����¼�����		
	}
	Shutdown();   // 3.������Ⱦ
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
