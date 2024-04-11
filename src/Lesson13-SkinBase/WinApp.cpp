#include <glad/glad.h>
#include "WinApp.h"
#include <stdlib.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#pragma region glfw���ڼ��¼�����
WinApp::WinApp()
{	
}

WinApp::~WinApp()
{	
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void WinApp::ErrorCallback(int error, const char* description)
{
}

void WinApp::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void WinApp::Initialize(int width, int height, const char* title)
{
	glfwSetErrorCallback(ErrorCallback);
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

	glfwSetKeyCallback(m_pWindow, KeyCallback);

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGL();
	// ��ֱͬ����1 �ر�0
	glfwSwapInterval(1);	
}

void WinApp::Run()
{
	Startup();    // 1.��Ⱦǰ׼������
	double curTime = 0;
	int num = 0;
	while (!glfwWindowShouldClose(m_pWindow))
	{
		// ����֡��
		curTime += m_Times.GetElapsedSecond();
		if (curTime >= 1.0f)
		{
			printf("��ǰ֡�ʣ�%d\r", num);
			num = 0; curTime = 0;
		}
		else
		{
			num++;
		}
		m_Times.UpDate();
		glfwGetFramebufferSize(m_pWindow, &m_Width, &m_Height);

		glViewport(0, 0, m_Width, m_Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		Render(); // 2.��ʼ��Ⱦ

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents(); // ��鴰�ڵ�ǰ�Ƿ����¼�����
	}
	Shutdown();   // 3.������Ⱦ
}
#pragma endregion 

void WinApp::Startup() 
{
	// 1.׼��Shader
	m_Shader.Initialize(); 

	// 2.׼������
	typedef struct Vertex
	{
		float x, y, z;
		float r, g, b, a;
		float u, v;

	} Vertex;

	static const Vertex vertices[6] =
	{
		//       ����                    ��ɫ                UV                
	   {  -1.0f,-1.0f, 0.0f ,  1.f, 0.f, 0.f,1.0f ,  0.0f,0.0f  },
	   {   1.0f,-1.0f, 0.0f ,  0.f, 1.f, 0.f,1.0f ,  1.0f,0.0f  },
	   {   1.0f, 1.0f, 0.0f ,  0.f, 0.f, 1.f,1.0f ,  1.0f,1.0f  },

	   {  -1.0f,-1.0f, 0.0f ,  1.f, 0.f, 0.f,1.0f ,  0.0f,0.0f  },
	   {   1.0f, 1.0f, 0.0f ,  0.f, 0.f, 1.f,1.0f ,  1.0f,1.0f  },
	   {  -1.0f, 1.0f, 0.0f ,  0.f, 1.f, 0.f,1.0f ,  0.0f,1.0f  },
	};

	
	// ShaderӦ�ð󶨶��㻺��������
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// �����Դ沢�򶥵㻺���������
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(m_Shader.m_Color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(m_Shader.m_Position);
	glEnableVertexAttribArray(m_Shader.m_Color);
	glEnableVertexAttribArray(m_Shader.m_UV);
}


void WinApp::Render()
{

	const float ratio = m_Width / (float)m_Height;
	glm::mat4 matModel(1), matProj(1), mp(1);	
	matModel = glm::scale(matModel, glm::vec3(0.5, 0.5, 0.5));
	matModel = glm::rotate(matModel, (float)glfwGetTime(), glm::vec3(1, 1, 1));
	matProj  = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);	
	mp = matProj * matModel;
	
	
	// ʹ��shader
	m_Shader.Begin();
	glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, glm::value_ptr(mp));
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	m_Shader.End();
	
}

void WinApp::Shutdown()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
