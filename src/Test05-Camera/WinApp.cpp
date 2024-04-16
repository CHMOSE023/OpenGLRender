#include <glad/glad.h>
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
	
}

bool         m_bRightFlg = false;
bool         m_bLeftFlg = false;
glm::dvec2   m_RightDowm;
glm::dvec2   m_LeftDowm;

void WinApp::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	WinApp* winApp = GetWindow(window);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{	
		m_bLeftFlg = true;
		m_LeftDowm = glm::dvec2(winApp->m_Xpos, winApp->m_Ypos);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		m_bLeftFlg = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		m_bRightFlg = true;
		m_RightDowm = glm::dvec2(winApp->m_Xpos, winApp->m_Ypos);
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		m_bRightFlg = false;
	}
}

glm::dvec3 CalcIntersectPoint(Ray& ray)
{
	glm::dvec3    pos     = ray.GetOrigin();
	//if (ray.GetDirection().y<=0.00)
	//{
	//	return glm::dvec3(0);
	//}
	//printf("pos.y %0.5f   ray.GetDirection().y  %0.5f \n", pos.y, ray.GetDirection().y);
	//printf("tm %0.5f\n", tm);

	double        tm      = abs((pos.y) / ray.GetDirection().y);
	
	//printf("tm %0.5f\n", tm);
	glm::dvec3    target  = ray.PointAt(tm);

	return  target;// glm::vec3(target.x, 0, target.z);
}



void WinApp::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	WinApp* winApp = GetWindow(window);
	winApp->m_Xpos = xpos;
	winApp->m_Ypos = ypos;	
	
	// �Ҽ�����ת
	if (m_bRightFlg)
	{
		glm::dvec2  offset = glm::dvec2(xpos, ypos) - m_RightDowm;
		m_RightDowm = glm::dvec2(xpos, ypos);
		// ����������ת
		winApp->m_camera.RotateViewY(offset.x * 0.01f);
		winApp->m_camera.RotateViewX(offset.y * 0.01f);
		winApp->m_camera.Update();
	}

	// ���ƽ��
	if (m_bLeftFlg)
	{
		glm::dvec2    pos(xpos, ypos);

		//std::cout << glm::to_string(pos) << std::endl;
		//std::cout << glm::to_string(m_LeftDowm) << std::endl;
		/**
		*   ���ȼ������һ�����غ͵�ǰ�����ı���
		*/
		Ray   ray0 = winApp->m_camera.CreateRayFromScreen(pos.x, pos.y);
		Ray   ray1 = winApp->m_camera.CreateRayFromScreen(m_LeftDowm.x, m_LeftDowm.y);
		
		//std::cout << "ray0" << glm::to_string(ray0.GetOrigin()) << std::endl;
		//std::cout << "ray1" << glm::to_string(ray1.GetOrigin()) << std::endl;

		glm::dvec3  pos0 = CalcIntersectPoint(ray0);
		glm::dvec3  pos1 = CalcIntersectPoint(ray1);
		
		glm::dvec3  offset3 = pos1 - pos0;
		
		//std::cout << "pos0" << glm::to_string(pos0) << std::endl;
		//std::cout << "pos1" << glm::to_string(pos1) << std::endl;
		//std::cout << "pos1" << glm::to_string(pos1) << std::endl;

		//std::cout << glm::to_string(offset3) << std::endl;
		
		//offset3 *= 100;
		
		m_LeftDowm = pos;
		//
		glm::dvec3  newEye = winApp->m_camera.GetEye()    + offset3 * 0.3;
		glm::dvec3  newTgt = winApp->m_camera.GetTarget() + offset3 * 0.3;
		
		// ������ת��� Y�� ���µ����߶�
		if (newEye.y > 100 || newEye.y < -10)
		{
			return;
		}
	

		winApp->m_camera.SetEye(newEye);
		winApp->m_camera.SetTarget(newTgt);
		// ��������
		//winApp->m_camera.SetUp(glm::cross(winApp->m_camera.GetRight(),glm::normalize(newTgt- newEye) ));
		std::cout << "Right" << glm::to_string(winApp->m_camera.GetRight()) << std::endl;
		
		// winApp->m_camera.SetUp(glm::dvec3(0, 1, 0));
		
		//std::cout <<"Eye" <<glm::to_string(winApp->m_camera.GetEye()) << std::endl;
		//std::cout <<"tgt" <<glm::to_string(winApp->m_camera.GetTarget()) << std::endl;
		 //std::cout <<"newEye" <<glm::to_string(newEye) << std::endl;
		// std::cout <<"newTgt" <<glm::to_string(newTgt) << std::endl;
		winApp->m_camera.Update();


	}
}

void WinApp::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	WinApp* winApp = GetWindow(window);
	winApp->m_Height = height;
	winApp->m_Width  = width;

	winApp->m_camera.Perspective(45.0f, float(width) / float(height), 0.1f, 500.0f);
	winApp->m_camera.SetViewSize(float(width), float(height));
}

// ������ת
void WinApp::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	WinApp* winApp = GetWindow(window);
	// �������������Ŀ������ m_camera-> m_radius
	double    persent = 1;

	if (yoffset > 0)
	{
		persent = 0.7;
	}
	else
	{
		persent = 1.3;
	}
	

	winApp->m_camera.SetEye(winApp->m_camera.GetEye() * persent);
	////winApp->m_camera.SetTarget(glm::dvec3(0, 0, 0));
	winApp->m_camera.Update();

	//glm::dvec3 upDir = glm::normalize(glm::dvec3(0,1,0));
	//
	//glm::dvec3 cameraEye = winApp->m_camera.GetEye() * persent;
	//
	//glm::dmat4 mat(1);
	//mat = glm::rotate(0.0, glm::dvec3(0, 1, 0));
	//
	//cameraEye = glm::dvec4(cameraEye,1) * mat;	
	//upDir     = glm::dvec4(upDir,1) * mat;
	//
	//winApp->m_camera.SetEye(cameraEye );
	//
	//glm::dvec3 cameraDir = winApp->m_camera.GetTarget() - winApp->m_camera.GetEye();
	//
	//cameraDir = glm::dvec4(cameraDir,1) * mat;
	//
	//glm::dvec3 cameraRight = glm::normalize(glm::cross(cameraDir, upDir));
	//
	//winApp->m_camera.SetRight(cameraRight);
	//winApp->m_camera.Update();


	//Ray  ray = winApp->m_camera.CreateRayFromScreen(winApp->m_Xpos, winApp->m_Ypos);
	//
	//glm::vec3  pos      = ray.GetOrigin();
	//float      tm       = abs((pos.y - 0) / ray.GetDirection().y);
	//glm::vec3  center   = ray.PointAt(tm);
	//           center.y = 0;
	////center.z = 0;
	////std::cout << glm::to_string(center) << std::endl;
	//winApp->m_camera.ScaleCameraByPos(center, persent);
	
	
				
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
	// ��������
	m_TextureCity  = LoadTexture("textures/chongqing.jpg");
	m_TextureGrass = LoadTexture("textures/grass.jpg");		
	m_TextureGrass1 = LoadTexture("textures/grass.png");		

	m_billboard.SetShader(m_Shader);
	


	// ��¼��һ֡��ʱ��
	m_LastFrameTime = glfwGetTime();

	// ���ý�ɫλ��
	m_Role.SetPosition(glm::vec3(0, 0.0f, -10));
	m_Role.SetTarget(glm::vec3(0, 0.0f, -10));


	// ���õ����˳����	
	m_camera.SetTarget(glm::dvec3(0, 0, 0));
	m_camera.SetEye(glm::dvec3(0, 100, 0));
	m_camera.SetRight(glm::dvec3(1, 0, 0));
	m_camera.CalcDir();

	m_camera.SetViewSize(m_Width, m_Height);
	m_camera.Perspective(45.0f, float(width) / float(height), 0.1f, 500.0f);
	
	m_camera.Update();
	
	

	// ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	
	// ������Ȼ���
	glEnable(GL_DEPTH_TEST);
	// ���û��
	glEnable(GL_BLEND);
	// ��Ϸ���
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
	//m_camera.SetTarget(m_Role.m_Position);                  // �����������ɫ
	//m_camera.Update();

	//  ���ƽ�ɫ
	m_Role.Render(deltaTime, m_camera, m_Shader, m_TextureCity, m_VertexArray, 6);
		
	// ���ƾ�̬�����
	m_billboard.Render(m_camera, m_TextureGrass1);
	// ���ƶ�̬�����
	m_billboard.Render(deltaTime,m_camera, m_TextureGrass1);

	//  ���Ƶ���
	RenderGround();

	
}

void WinApp::RenderGround()
{
	glm::mat4  mvp;
	glm::mat4  matView     = m_camera.GetView();
	glm::mat4  matProj     = m_camera.GetProject();
	glm::mat4  matModel    = glm::mat4x4(1.0);

	float     angle = glfwGetTime();
	glm::vec3  axis(0.0f, 1.0f, 0.0f); // ��ת��	
    
	//matModel=glm::rotate(matModel, angle, axis);

	mvp = matProj * matView * matModel;

	// ʹ������2 ���Ƶ���
	m_Shader.Begin();
	glBindTexture(GL_TEXTURE_2D, m_TextureGrass);// ʹ������2
	glBindVertexArray(m_Grounds);
	glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);
	glDrawArrays(GL_TRIANGLES, 0, 6);
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

