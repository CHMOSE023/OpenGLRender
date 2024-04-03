#pragma once
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
#include "linmath.h"


typedef struct Vertex
{
	vec3 pos;
	vec4 col;
	vec2 uv;
} Vertex;


class WinApp
{
typedef Shader_P3_C4_T2 Shaders;

public:
	WinApp();
	~WinApp();
	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Initialize(int width, int height, const char* title);  // Èë¿Úº¯Êý
	void Run();
	void Render();
	GLuint LoadTexture(const char* fileName);
	
public:
	int           m_Width;
	int	          m_Height;
	GLFWwindow*   m_pWindow;	
	Shaders       m_Shader;
	GLuint        m_VertexArray;
	GLuint        m_Grounds;
	GLuint        m_TextureCity;
	GLuint        m_TextureGrass;

};

