#pragma once
#include <string>
#include "Shader_P3_C3.h"
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>


class WinApp
{
typedef Shader_P3_C3 Shaders;

public:
	WinApp();
	~WinApp();
	static void ErrorCallback(int error, const char* description);
	static WinApp* GetWindow(GLFWwindow* window);
	void Initialize(int width, int height, const char* title); 
	void OnInit(); // ��ʼ����
	void Destroy();// ��������
	void Run();
	void Render();
	GLuint LoadTexture(const char* fileName);
	
public:
	int           m_Width;
	int	          m_Height;
	unsigned int  m_VAO;     // ���㻺����
	unsigned int  m_VBO;     // ����������
	unsigned int  m_EBO;     // ����������
	GLFWwindow*   m_pWindow;	
	Shaders       m_Shader;
};

