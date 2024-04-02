#pragma once
#include "Program_P2_C4.h"
#include <GLFW/glfw3.h>
#include "linmath.h"

typedef struct Vertex
{
	vec2 pos;
	vec3 col;
} Vertex;


class WinApp
{
public:
	WinApp();
	~WinApp();
	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Initialize(int width, int height, const char* title);  // Èë¿Úº¯Êý
	void Run();
	void Render();
	
public:
	int           m_Width;
	int	          m_Height;
	GLFWwindow*   m_pWindow;	
	PROGRAM_P2_C4 m_Shader;
	GLuint        m_VertexArray;

};

