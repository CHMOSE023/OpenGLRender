
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
	glfwMakeContextCurrent(m_pWindow);

	// �����û����ݣ���¼��ǰ��ָ��
	glfwSetWindowUserPointer(m_pWindow, this);

	gladLoadGL();
	glfwSwapInterval(1);

	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	// ��ʼ�� shader
	m_Shader.Initialize();

	// ��ʼ������
	OnInit();
	
}

void WinApp::OnInit()    // ����ʼ������
{
	
	glGenVertexArrays(1, &m_VAO); // ��������������� VAO	
	glGenBuffers(1, &m_VBO);      // �������㻺����� VBO	
	glGenBuffers(1, &m_EBO);      // ��������������� EBO

	glBindVertexArray(m_VAO);     // �� VAO

	// �� VBO ���������
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeVertices), g_cubeVertices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(m_Shader.m_Position);

	// ����UV����ָ��
	glVertexAttribPointer(m_Shader.m_UV, 2,       GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(m_Shader.m_UV);

	// ������ɫ����ָ��
	glVertexAttribPointer(m_Shader.m_Color, 4,    GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)20);
	glEnableVertexAttribArray(m_Shader.m_Color);

	//! ��ʼ��FBO
	m_FBO.Create(m_Width, m_Height);

	//����ʼ������
	m_DynamicTexture = CreateTexture(m_FBO.m_Width, m_FBO.m_Height, GL_RGBA, GL_RGBA, 0);
	m_TextureId = LoadTexture("textures/chongqing.jpg");
	
}


void WinApp::Destroy()   // ����������
{	
	// ��������
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteTextures(1, &m_DynamicTexture);
}

void WinApp::DrawCube(int viewW, int viewH)
{
	glBindVertexArray(m_VAO);

	glm::mat4 mvp;

	{	// ����mvp	
		// �������
		glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 2.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -100.0f);
		glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

		// ����ģ�;���
		glm::mat4 model = glm::mat4(1.0f); // ��ʼ��Ϊ��λ����
		model = glm::translate(model, glm::vec3(0, 0, -3));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f)); // ����ָ������ת

		// ���ù۲����
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		// ����ͶӰ����
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(viewW) / float(viewH), 0.1f, 100000.0f);

		mvp = projection * view * model;
	}

	m_Shader.Begin();
	glUniformMatrix4fv(m_Shader.m_MVP, 1, false, (const GLfloat*)&mvp);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(g_cubeVertices) / sizeof(g_cubeVertices[0]));
	m_Shader.End();

	//glBindVertexArray(0);
}

void WinApp::Render()   // ����Ⱦ
{
	m_FBO.Begin(m_DynamicTexture); // �� ��̨���Ƶ� m_DynamicTexture ������
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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



unsigned int WinApp::CreateTexture(int width, int height, unsigned inteFmt, unsigned dataFmt, void* data)
{
	unsigned  int  texId = 0;
	
	// ����һ������Id,������Ϊ��������������Ĳ����������������id
	glGenTextures(1, &texId);
	
	// ʹ���������id,���߽а�(����)
	glBindTexture(GL_TEXTURE_2D, texId);

    //  ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//  ��ͼƬ��rgb�����ϴ���opengl.
	glTexImage2D(
		GL_TEXTURE_2D,      //! ָ���Ƕ�άͼƬ
		0,                  //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
		inteFmt,            //! �����ʹ�õĴ洢��ʽ
		width,              //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
		height,             //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
		0,                  //! �Ƿ�ı�
		dataFmt,            //! ���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,   //! ������8bit����
		data
	);
	return  texId;
}

