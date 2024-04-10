#pragma once
#include "Shader_P3_T2.h"
#include <GLFW/glfw3.h>
#include "linmath.h"


struct Vertex
{
	float x, y, z;
	float u, v;
};

class WinApp
{
typedef Shader_P3_T2 Shaders;

public:
	WinApp();
	~WinApp();
	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Initialize(int width, int height, const char* title);  // Èë¿Úº¯Êý
	void Run();
	void Render();
	void LoadTexture(const char* fileName);
	
public:
	int           m_Width;
	int	          m_Height;
	GLFWwindow*   m_pWindow;	
	Shaders       m_Shader;
	GLuint        m_Texture;
	GLuint        m_VAO;
	GLuint        m_VBO;
	

};

