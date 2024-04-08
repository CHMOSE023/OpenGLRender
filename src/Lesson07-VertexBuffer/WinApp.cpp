#include <glad/glad.h>
#include "WinApp.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#include <math.h>
#include <Windows.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

WinApp::WinApp() :m_pWindow(nullptr), m_Width(0), m_Height(0)
{
	
}

WinApp::~WinApp()
{
	Destroy();
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void WinApp::ErrorCallback(int error, const char* description)
{

}


// 获取 glfw 窗口的用户数据，转换成 WinApp类指针。
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
	glfwMakeContextCurrent(m_pWindow);

	// 设置用户数据，记录当前类指针
	glfwSetWindowUserPointer(m_pWindow, this);

	gladLoadGL();
	glfwSwapInterval(1);
	//glDisable(GL_CULL_FACE);    // 禁用背面剔除
	//glEnable(GL_DEPTH_TEST); 	// 启动深度缓冲

	// 初始化 shader
	m_Shader.Initialize();

	// 初始化数据
	OnInit();
	
}

void WinApp::OnInit()    // ！初始化数据
{
	glViewport(0, 0, m_Width, m_Height);

	// 正方形的顶点数据
	float vertices[] = {
		   // 位置                 // 颜色
		 0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f,  // 右上角 红色
		 0.5f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f,  // 右下角 绿色
		-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f,  // 左下角 蓝色
		-0.5f,  0.5f, 0.0f,  1.0f,  1.0f, 0.0f   // 左上角 黄色
	};

	unsigned int indices[] = {
		0, 1, 3,   // 第一个三角形
		1, 2, 3    // 第二个三角形
	};

	
	glGenVertexArrays(1, &m_VAO); // 创建顶点数组对象 VAO	
	glGenBuffers(1, &m_VBO);      // 创建顶点缓冲对象 VBO	
	glGenBuffers(1, &m_EBO);      // 创建索引缓冲对象 EBO
	
	glBindVertexArray(m_VAO);     // 绑定 VAO

	// 绑定 VBO 并填充数据
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定 EBO 并填充数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 解绑 VAO
	glBindVertexArray(0);

}


void WinApp::Destroy()   // ！销毁数据
{	
	// 清理数据
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}



void WinApp::Render()   // ！渲染
{
	
	glm::mat4 mvp;

	{	// 计算mvp	
		// 相机参数
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -100.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		// 设置模型矩阵
		glm::mat4 model = glm::mat4(1.0f); // 初始化为单位矩阵
		//model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕着指定轴旋转

		// 设置观察矩阵
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		// 设置投影矩阵
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(m_Width) / float(m_Height), 0.1f, 100000.0f);
		
		{  /* 正交投影*/
			//float left = -1.0f;
			//float right = 1.0f;
			//float bottom = -1.0f;
			//float top = 1.0f;
			//float near1 = 0.1f;
			//float far1 = 100.0f;
			//glm::mat4 projection = glm::ortho(left, right, bottom, top, near1, far1);
		}	

		mvp = projection * view * model;
	}


	// 绘制三角形	
	m_Shader.Begin();
	glUniformMatrix4fv(m_Shader.m_MVP, 1,false, (const GLfloat*)&mvp);		
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_Shader.End();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void WinApp::Run()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwGetFramebufferSize(m_pWindow, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Render();

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
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

