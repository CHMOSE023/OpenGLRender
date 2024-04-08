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
	//glDisable(GL_CULL_FACE);    // ���ñ����޳�
	//glEnable(GL_DEPTH_TEST); 	// ������Ȼ���

	// ��ʼ�� shader
	m_Shader.Initialize();

	// ��ʼ������
	OnInit();
	
}

void WinApp::OnInit()    // ����ʼ������
{
	glViewport(0, 0, m_Width, m_Height);

	// �����εĶ�������
	float vertices[] = {
		   // λ��                 // ��ɫ
		 0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f,  // ���Ͻ� ��ɫ
		 0.5f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f,  // ���½� ��ɫ
		-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, 1.0f,  // ���½� ��ɫ
		-0.5f,  0.5f, 0.0f,  1.0f,  1.0f, 0.0f   // ���Ͻ� ��ɫ
	};

	unsigned int indices[] = {
		0, 1, 3,   // ��һ��������
		1, 2, 3    // �ڶ���������
	};

	
	glGenVertexArrays(1, &m_VAO); // ��������������� VAO	
	glGenBuffers(1, &m_VBO);      // �������㻺����� VBO	
	glGenBuffers(1, &m_EBO);      // ��������������� EBO
	
	glBindVertexArray(m_VAO);     // �� VAO

	// �� VBO ���������
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// �� EBO ���������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��� VAO
	glBindVertexArray(0);

}


void WinApp::Destroy()   // ����������
{	
	// ��������
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}



void WinApp::Render()   // ����Ⱦ
{
	
	glm::mat4 mvp;

	{	// ����mvp	
		// �������
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -100.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		// ����ģ�;���
		glm::mat4 model = glm::mat4(1.0f); // ��ʼ��Ϊ��λ����
		//model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // ����ָ������ת

		// ���ù۲����
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		// ����ͶӰ����
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(m_Width) / float(m_Height), 0.1f, 100000.0f);
		
		{  /* ����ͶӰ*/
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


	// ����������	
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

