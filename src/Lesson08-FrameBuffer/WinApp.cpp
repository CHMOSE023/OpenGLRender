
#include "WinApp.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#include <math.h>
#include <Windows.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

struct  Vertex
{
	float   x, y, z;
	float   u, v;
	float   r, g, b, a;
};

Vertex g_cubeVertices[] =
{
	// Quad 0
	{ -1.0f,-1.0f, 1.0f,0,1,1.0f,1.0f,1.0f,1.0f },
	{  1.0f,-1.0f, 1.0f,1,1,1.0f,1.0f,1.0f,1.0f  },
	{  1.0f, 1.0f, 1.0f,1,0,1.0f,1.0f,1.0f,1.0f  },

	{ -1.0f,-1.0f, 1.0f,0,1,1.0f,1.0f,1.0f,1.0f  },
	{  1.0f, 1.0f, 1.0f,1,0,1.0f,1.0f,1.0f,1.0f  },
	{ -1.0f, 1.0f, 1.0f,0,0,1.0f,1.0f,1.0f,1.0f  },
	//
	{ -1.0f,-1.0f,-1.0f,0,1,1.0f,0.0f,0.0f,1.0f  },
	{ -1.0f, 1.0f,-1.0f,1,1,1.0f,0.0f,0.0f,1.0f  },
	{  1.0f, 1.0f,-1.0f,1,0,1.0f,0.0f,0.0f,1.0f  },

	{ -1.0f,-1.0f,-1.0f,0,1,1.0f,0.0f,0.0f,1.0f  },
	{  1.0f, 1.0f,-1.0f,1,0,1.0f,0.0f,0.0f,1.0f  },
	{  1.0f,-1.0f,-1.0f,0,0,1.0f,0.0f,0.0f,1.0f  },

	//
	{ -1.0f, 1.0f,-1.0f,0,1,0.0f,1.0f,0.0f,1.0f },
	{ -1.0f, 1.0f, 1.0f,1,1,0.0f,1.0f,0.0f,1.0f },
	{  1.0f, 1.0f, 1.0f,1,0,0.0f,1.0f,0.0f,1.0f },

	{ -1.0f, 1.0f,-1.0f,0,1,0.0f,1.0f,0.0f,1.0f },
	{  1.0f, 1.0f, 1.0f,1,0,0.0f,1.0f,0.0f,1.0f },
	{  1.0f, 1.0f,-1.0f,0,0,0.0f,1.0f,0.0f,1.0f },

	//
	{ -1.0f,-1.0f,-1.0f,0,1,0.0f,1.0f,0.0f,1.0f },
	{  1.0f,-1.0f,-1.0f,1,1,0.0f,1.0f,0.0f,1.0f },
	{  1.0f,-1.0f, 1.0f,1,0,0.0f,1.0f,0.0f,1.0f },

	{ -1.0f,-1.0f,-1.0f,0,1,0.0f,1.0f,0.0f,1.0f },
	{  1.0f,-1.0f, 1.0f,1,0,0.0f,1.0f,0.0f,1.0f },
	{ -1.0f,-1.0f, 1.0f,0,0,0.0f,1.0f,0.0f,1.0f},

	// Quad 4
	{  1.0f,-1.0f,-1.0f,0,1,0.0f,0.0f,1.0f,1.0f },
	{  1.0f, 1.0f,-1.0f,1,1,0.0f,0.0f,1.0f,1.0f },
	{  1.0f, 1.0f, 1.0f,1,0,0.0f,0.0f,1.0f,1.0f },

	{  1.0f,-1.0f,-1.0f,0,1,0.0f,0.0f,1.0f,1.0f },
	{  1.0f, 1.0f, 1.0f,1,0,0.0f,0.0f,1.0f,1.0f },
	{  1.0f,-1.0f, 1.0f,0,0,0.0f,0.0f,1.0f,1.0f },

	//
	{ -1.0f,-1.0f,-1.0f,0,1,0.0f,0.0f,1.0f,1.0f },
	{ -1.0f,-1.0f, 1.0f,1,1,0.0f,0.0f,1.0f,1.0f },
	{ -1.0f, 1.0f, 1.0f,1,0,0.0f,0.0f,1.0f,1.0f },

	{ -1.0f,-1.0f,-1.0f,0,1,0.0f,0.0f,1.0f,1.0f },
	{ -1.0f, 1.0f, 1.0f,1,0,0.0f,0.0f,1.0f,1.0f },
	{ -1.0f, 1.0f,-1.0f,0,0,0.0f,0.0f,1.0f,1.0f }
};


WinApp::WinApp() 
{
	m_TextureId = -1;	
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

	// 启动深度测试
	glEnable(GL_DEPTH_TEST);

	// 初始化 shader
	m_Shader.Initialize();

	// 初始化数据
	OnInit();
	
}

void WinApp::OnInit()    // ！初始化数据
{
	
	glGenVertexArrays(1, &m_VAO); // 创建顶点数组对象 VAO	
	glGenBuffers(1, &m_VBO);      // 创建顶点缓冲对象 VBO	
	glGenBuffers(1, &m_EBO);      // 创建索引缓冲对象 EBO

	glBindVertexArray(m_VAO);     // 绑定 VAO

	// 绑定 VBO 并填充数据
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeVertices), g_cubeVertices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(m_Shader.m_Position);

	// 设置UV属性指针
	glVertexAttribPointer(m_Shader.m_UV, 2,       GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(m_Shader.m_UV);

	// 设置颜色属性指针
	glVertexAttribPointer(m_Shader.m_Color, 4,    GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)20);
	glEnableVertexAttribArray(m_Shader.m_Color);

	//! 初始化FBO
	m_FBO.Create(m_Width, m_Height);

	//！初始化纹理
	m_DynamicTexture = CreateTexture(m_FBO.m_Width, m_FBO.m_Height, GL_RGBA, GL_RGBA, 0);
	m_TextureId = LoadTexture("textures/chongqing.jpg");
	
}


void WinApp::Destroy()   // ！销毁数据
{	
	// 清理数据
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteTextures(1, &m_DynamicTexture);
}

void WinApp::DrawCube(int viewW, int viewH)
{
	glBindVertexArray(m_VAO);

	glm::mat4 mvp;

	{	// 计算mvp	
		// 相机参数
		glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 2.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -100.0f);
		glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

		// 设置模型矩阵
		glm::mat4 model = glm::mat4(1.0f); // 初始化为单位矩阵
		model = glm::translate(model, glm::vec3(0, 0, -3));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f)); // 绕着指定轴旋转

		// 设置观察矩阵
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		// 设置投影矩阵
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(viewW) / float(viewH), 0.1f, 100000.0f);

		mvp = projection * view * model;
	}

	m_Shader.Begin();
	glUniformMatrix4fv(m_Shader.m_MVP, 1, false, (const GLfloat*)&mvp);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(g_cubeVertices) / sizeof(g_cubeVertices[0]));
	m_Shader.End();

	//glBindVertexArray(0);
}

void WinApp::Render()   // ！渲染
{
	m_FBO.Begin(m_DynamicTexture); // ！ 后台绘制到 m_DynamicTexture 纹理中
	{
	   glClearColor(1, 1, 1, 1);
	   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	   glViewport(0, 0, m_FBO.m_Width, m_FBO.m_Height);
	   glBindTexture(GL_TEXTURE_2D, m_TextureId);
	   DrawCube(m_FBO.m_Width, m_FBO.m_Height);
	}

	m_FBO.End();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, m_Width, m_Height);
	glBindTexture(GL_TEXTURE_2D, m_DynamicTexture);
	DrawCube(m_Width, m_Height);

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



unsigned int WinApp::CreateTexture(int width, int height, unsigned inteFmt, unsigned dataFmt, void* data)
{
	unsigned  int  texId = 0;
	
	// 产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
	glGenTextures(1, &texId);
	
	// 使用这个纹理id,或者叫绑定(关联)
	glBindTexture(GL_TEXTURE_2D, texId);

    //  指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//  将图片的rgb数据上传给opengl.
	glTexImage2D(
		GL_TEXTURE_2D,      //! 指定是二维图片
		0,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
		inteFmt,            //! 纹理的使用的存储格式
		width,              //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
		height,             //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
		0,                  //! 是否的边
		dataFmt,            //! 数据的格式
		GL_UNSIGNED_BYTE,   //! 数据是8bit数据
		data
	);
	return  texId;
}

