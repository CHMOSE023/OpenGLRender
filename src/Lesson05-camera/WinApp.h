#pragma once
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
#include "linmath.h"

#include "../Core/CameraBase.h"

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
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static WinApp* GetWindow(GLFWwindow* window);
	void Initialize(int width, int height, const char* title);  // 入口函数
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
	CameraBase    m_CameraBase;
	float         m_LastFrameTime;// 记录上一帧的时间
		
	

};

