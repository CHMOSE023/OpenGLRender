#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WinApp.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#include <math.h>
#include <Windows.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>


WinApp::WinApp() :m_pWindow(nullptr), m_Width(0), m_Height(0), m_VertexArray(0)
{
	 m_VertexArray   = -1;
	 m_Grounds       = -1;
	 m_TextureCity   = -1;
	 m_TextureGrass  = -1;	
	 m_LastFrameTime = -1;
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

// ������Ϣ
void WinApp::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{		
	//printf("Key:\t%d,%d,%d,%d\r", key, scancode, action, mods);	
}

bool  bRightFlg = false;
glm::vec2 m_RightDowm;
void WinApp::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	WinApp* winApp = GetWindow(window);
	

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// ��������ȡ����
		Ray ray = winApp->m_ThirdCamera.CreateRayFromScreen(winApp->m_Xpos, winApp->m_Ypos);
		// ����������ƽ�潻��
		glm::vec3  dir = ray.GetDirection();
		glm::vec3  pos = ray.GetOrigin();
		float      tm  = abs((pos.y) / dir.y);
		glm::vec3  tp  = ray.PointAt(tm);
		//std::cout << glm::to_string(tp) << std::endl;
		winApp->m_Role.SetTarget(tp);

	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		
	}
	
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		bRightFlg = true;
		m_RightDowm = glm::vec2(winApp->m_Xpos, winApp->m_Ypos);
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		bRightFlg = false;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
	
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		
	}

	//printf("CursorPosition:\txpos %0.3f,ypos %0.3f\n", winApp->m_Xpos, winApp->m_Ypos);
	//printf("Mouse:\t%d,%d,%d\n", button, action, mods);
}

void WinApp::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	WinApp* winApp = GetWindow(window);
	winApp->m_Xpos = xpos;
	winApp->m_Ypos = ypos;	

	if (bRightFlg)
	{
		glm::vec2  offset = glm::vec2(xpos, ypos) - m_RightDowm;
		m_RightDowm = glm::vec2(xpos, ypos);
		winApp->m_ThirdCamera.RotateView(offset.x * 0.01f);
		winApp->m_ThirdCamera.Update();
	}
	
}

void WinApp::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	WinApp* winApp = GetWindow(window);
	winApp->m_Height = height;
	winApp->m_Width  = width;

	winApp->m_ThirdCamera.Perspective(45.0f, float(width) / float(height), 0.1f, 100000.0f);
	winApp->m_ThirdCamera.SetViewSize(float(width), float(height));
}

void WinApp::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	WinApp* winApp = GetWindow(window);
	if (yoffset > 0)
	{
		winApp->m_ThirdCamera.SetRadius(winApp->m_ThirdCamera.GetRadius() * 1.2f);
		winApp->m_ThirdCamera.Update();
	}
	else if (yoffset < 0)
	{
		winApp->m_ThirdCamera.SetRadius(winApp->m_ThirdCamera.GetRadius() * 0.8f);
		winApp->m_ThirdCamera.Update();
	}
}

// ��ȡ glfw ���ڵ��û����ݣ�ת���� WinApp��ָ�롣
WinApp* WinApp::GetWindow(GLFWwindow* window)
{
	void* userdata = glfwGetWindowUserPointer(window);
	return reinterpret_cast<WinApp*>(userdata);
}


void WinApp::Initialize(int width, int height,const char*title)
{
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow=  glfwCreateWindow(width, height, title, NULL, NULL);
	m_Width = width;
	m_Height = height;

	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
			
	// ����glfw�ص�����
	glfwSetKeyCallback(m_pWindow, KeyCallback);
	glfwSetMouseButtonCallback(m_pWindow, MouseButtonCallback);
	glfwSetCursorPosCallback(m_pWindow, CursorPositionCallback);
	glfwSetWindowSizeCallback(m_pWindow, WindowSizeCallback);
	glfwSetScrollCallback(m_pWindow,ScrollCallback);
	//glfwSetFramebufferSizeCallback(m_pWindow, FramebufferSizeCallback);

	glfwMakeContextCurrent(m_pWindow);

	// �����û����ݣ���¼��ǰ��ָ��
	glfwSetWindowUserPointer(m_pWindow, this);

	gladLoadGL();
	glfwSwapInterval(1);

	// ���ñ����޳�
	glDisable(GL_CULL_FACE);

	// ��ʼ�� shader
	m_Shader.Initialize();
	m_ShaderDirLight.Initialize();

	// ��������
	m_TextureCity  = LoadTexture("textures/grass.png");
	m_TextureGrass = LoadTexture("textures/grass.jpg");	


	// ��¼��һ֡��ʱ��
	m_LastFrameTime = glfwGetTime();

	// ���õ����˳����	
	m_ThirdCamera.SetRadius(50.0f);
	m_ThirdCamera.SetViewSize(m_Width, m_Height);
	m_ThirdCamera.Perspective(45.0f, float(width) / float(height), 0.1f, 100000.0f);
	m_ThirdCamera.SetEye(glm::vec3(50, 50, 50));
	m_ThirdCamera.SetTarget(m_Role.m_Position);
	m_ThirdCamera.CalcDir();
	m_ThirdCamera.SetUp(glm::vec3(0,1.0f,0));	
	m_ThirdCamera.Update();

	// ���ý�ɫλ��
	m_Role.SetPosition(glm::vec3(0, 0.0f, -10));
	m_Role.SetTarget(glm::vec3(0, 0.0f, -10));

	//unsigned vao, vbo, ebo;
	//
	// glGenVertexArrays(1, &vao); // ��������������� VAO	
    // glGenBuffers(1, &vbo);      // �������㻺����� VBO	
    // glGenBuffers(1, &ebo);      // ��������������� EBO
	//m_ModelStd.Load("model/MouseMesh.sm", vao, vbo, ebo);
	  
	// ��ȡxmlģ������
	m_pModelStd = new ModelStd();
	m_pModelStd->Load("model/MouseMesh.sm");
	//m_ModelStd.Load("model/MouseMesh.sm");

	// ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	// ���û��
	//glEnable(GL_BLEND);
	// ��Ϸ���
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	
	
	// ��ɫ����
	static const Vertex vertices[6] =
	{
		 //       ����                    ��ɫ                UV                
		{ { -1.0f,-1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		{ {  1.0f,-1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,0.0f } },
		{ {  1.0f, 1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,1.0f }},

		{ { -1.0f,-1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		{ {  1.0f, 1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,1.0f } },
	    { { -1.0f, 1.0f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,1.0f } }

	};

	// �����Դ沢�򶥵㻺���������
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ShaderӦ�ð󶨶��㻺��������
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);
	glEnableVertexAttribArray(m_Shader.m_Position);
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(m_Shader.m_Color);
	glVertexAttribPointer(m_Shader.m_Color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(m_Shader.m_UV);
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);



	float   gSize = 100;
	float   gPos = -5;
	float   rept = 20;

	// ���Ƶ�������	
	static const Vertex grounds[6] =
	{
		//       ����                    ��ɫ                   UV                
	   { { -gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
	   { {  gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,0.0f } },
	   { {  gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,rept }},

	   { { -gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
	   { {  gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,rept } },
	   { { -gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{   0.0f,rept } }
	
	};

	// �����Դ沢�򶥵㻺���������
	GLuint grounds_buffer;
	glGenBuffers(1, &grounds_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, grounds_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grounds), grounds, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Grounds);
	glBindVertexArray(m_Grounds);
	glEnableVertexAttribArray(m_Shader.m_Position);
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(m_Shader.m_Color);
	glVertexAttribPointer(m_Shader.m_Color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(m_Shader.m_UV);
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	
}


void WinApp::Run()
{		
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwGetFramebufferSize(m_pWindow, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);
		
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		Render();

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

void WinApp::Render()
{	
	double currentFrameTime = glfwGetTime();                // ��ȡ��ǰ֡��ʱ��
	double deltaTime = currentFrameTime - m_LastFrameTime;  // ����֡���	
	m_LastFrameTime = currentFrameTime;                     // ������һ֡ʱ��

	// �������
	m_ThirdCamera.SetTarget(m_Role.m_Position);             // �����������ɫ
	m_ThirdCamera.Update();

	// ���ƽ�ɫ
	glBindVertexArray(m_VertexArray);
	m_Role.Render(deltaTime, m_ThirdCamera, m_Shader, m_TextureCity, m_VertexArray, 6);
	

	// ����ģ��
	m_pModelStd->Render(m_LastFrameTime, m_ThirdCamera, m_ShaderDirLight);
	//m_ModelStd.Render(m_LastFrameTime, m_ThirdCamera,m_ShaderDirLight);
	
	//  ���Ƶ���
	RenderGround();
}

void WinApp::RenderGround()
{
	glm::mat4  mvp;
	glm::mat4  matView     = m_ThirdCamera.GetView();
	glm::mat4  matProj     = m_ThirdCamera.GetProject();
	glm::mat4  matModel    = glm::mat4x4(1.0);

	float     angle = glfwGetTime();
	glm::vec3  axis(0.0f, 1.0f, 0.0f); // ��ת��	

	mvp = matProj * matView * matModel;
	
	// ʹ������2 ���Ƶ���
	m_Shader.Begin();
	glBindTexture(GL_TEXTURE_2D, m_TextureGrass);// ʹ������2
	glBindVertexArray(m_Grounds);
	glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	m_Shader.End();
}

GLuint WinApp::LoadTexture(const char* fileName)
{
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); 

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ��תͼ��
	stbi_set_flip_vertically_on_load(true);
	// ���ز���������
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("����ʧ��\n");
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

