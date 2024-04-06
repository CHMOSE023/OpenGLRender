#include <glad/glad.h>
#include "WinApp.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>

WinApp::WinApp() :m_pWindow(nullptr), m_Width(0), m_Height(0), m_VertexArray(0)
{
	 m_VertexArray  = -1;
	 m_Grounds      = -1;
	 m_TextureCity  = -1;
	 m_TextureGrass = -1;
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
// 键盘消息
void WinApp::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  //	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  //		glfwSetWindowShouldClose(window, GLFW_TRUE); // 关闭窗口

	printf("Key:\t%d,%d,%d,%d\n", key, scancode, action, mods);

}

void WinApp::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	printf("Mouse:\t%d,%d,%d\n", button, action, mods);
}

void WinApp::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	printf("CursorPosition:\txpos %0.3f,ypos %0.3f\n", xpos, ypos);
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
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// 设置glfw回调函数
	glfwSetKeyCallback(m_pWindow, KeyCallback);
	glfwSetMouseButtonCallback(m_pWindow, MouseButtonCallback);
	glfwSetCursorPosCallback(m_pWindow, CursorPositionCallback);

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGL();
	glfwSwapInterval(1);

	// 初始化 shader
	m_Shader.Initialize();
	// 加载纹理
	m_TextureCity  = LoadTexture("textures/chongqing.jpg");
	m_TextureGrass = LoadTexture("textures/grass.jpg");
	// 启动深度缓冲
	glEnable(GL_DEPTH_TEST);
	
	static const Vertex vertices[6] =
	{
		 //       顶点                    颜色                UV                
		{ { -1.0f,-1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		{ {  1.0f,-1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,0.0f } },
		{ {  1.0f, 1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,1.0f }},

		{ { -1.0f,-1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		{ {  1.0f, 1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  1.0f,1.0f } },
	    { { -1.0f, 1.0f, 5.0f }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,1.0f } }

	};

	// 创建显存并向顶点缓冲填充数据
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader应用绑定顶点缓冲区数据
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);
	glEnableVertexAttribArray(m_Shader.m_Position);
	glVertexAttribPointer(m_Shader.m_Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(m_Shader.m_Color);
	glVertexAttribPointer(m_Shader.m_Color, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(m_Shader.m_UV);
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 绘制地面数据	
	static const Vertex grounds[6] =
	{
		//       顶点                    颜色                UV                
	   { { -1.5f,-1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{   0.0f, 0.0f } },
	   { {  1.5f,-1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  10.0f, 0.0f } },
	   { {  1.5f, 1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  10.0f,10.0f }},
	
	   { { -1.5f,-1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{   0.0f, 0.0f } },
	   { {  1.5f, 1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{  10.0f,10.0f } },
	   { { -1.5f, 1.5f, 0.0f }, { 1.f, 1.f, 1.f,1.0f },{   0.0f,10.0f } }
	
	};


	// 创建显存并向顶点缓冲填充数据
	GLuint grounds_buffer;
	glGenBuffers(1, &grounds_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, grounds_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grounds), grounds, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Grounds);
	glBindVertexArray(m_Grounds);
	glEnableVertexAttribArray(m_Shader.m_Position);
	glVertexAttribPointer(m_Shader.m_Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(m_Shader.m_Color);
	glVertexAttribPointer(m_Shader.m_Color, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(m_Shader.m_UV);
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

#include <string>
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
	const float PI = 3.1415926;
	const float ratio = m_Width / (float)m_Height;
	mat4x4 m, p, mvp;
	mat4x4_identity(m);	
	// ！模型向后移动才能看到
	mat4x4_translate(m, 0, 0,-3.0f);
	
	mat4x4_rotate_Y(m, m, (float)glfwGetTime()*.5);
     mat4x4_rotate_X(m, m, (float)glfwGetTime());
	mat4x4_rotate_Z(m, m, (float)glfwGetTime());
	// 透视投影
	mat4x4_perspective(p, 45, ratio, 0.1f, 100.0f);	
	mat4x4_mul(mvp, p, m);

	// 使用shader
	m_Shader.Begin();


	// 使用纹理1 绘制旋转物体
	glBindTexture(GL_TEXTURE_2D, m_TextureCity); 
	glBindVertexArray(m_VertexArray);
	glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);	
	glDrawArrays(GL_TRIANGLES, 0, 6);


	// 使用纹理2 绘制地面
	mat4x4_identity(m);		
	mat4x4_translate(m, 0, -6.0, -12.0f);
	mat4x4_scale_aniso(m, m, 30, 30, 1);
	mat4x4_rotate_X(m, m, PI *.5);
	mat4x4_perspective(p, 45, ratio, 0.1f, 100.0f);
	mat4x4_mul(mvp, p, m);

	glBindTexture(GL_TEXTURE_2D, m_TextureGrass);// 使用纹理2
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

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 翻转图像
	stbi_set_flip_vertically_on_load(true);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("加载失败\n");
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

