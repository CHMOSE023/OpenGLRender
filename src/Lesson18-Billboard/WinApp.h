#pragma once
#include <string>
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
//#include "linmath.h"
#include "ThirdCamera.h"
#include "Role.h"
#include "Billboard.h"

typedef struct Vertex
{
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec2 uv;
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
	static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static WinApp* GetWindow(GLFWwindow* window);
	void Initialize(int width, int height, const char* title);  // 入口函数
	void Run();
	void Render();
	void RenderGround();
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
	GLuint        m_TextureGrass1;
	ThirdCamera   m_ThirdCamera;
	Role          m_Role;
	float         m_LastFrameTime;// 记录上一帧的时间		
	double        m_Xpos;
	double        m_Ypos;

	Billboard     m_billboard;

};

