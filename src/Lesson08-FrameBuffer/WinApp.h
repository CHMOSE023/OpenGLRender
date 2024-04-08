#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "FrameBuffer.h"
#include "Shader_P2_T2_C3.h"

class WinApp
{
typedef Shader_P2_T2_C3 Shaders;

public:
	WinApp();
	~WinApp();
	static void ErrorCallback(int error, const char* description);
	static WinApp* GetWindow(GLFWwindow* window);
	void Initialize(int width, int height, const char* title); 
	void OnInit(); // 初始数据
	void Destroy();// 销毁数据
	void Run();
	void Render();
	GLuint LoadTexture(const char* fileName);
	void  DrawCube(int viewW, int viewH);
	unsigned int   CreateTexture(int width, int height, unsigned inteFmt, unsigned dataFmt, void* data);
	
public:
	int           m_Width;
	int	          m_Height;
	unsigned int  m_VAO;     // 顶点缓冲区
	unsigned int  m_VBO;     // 索引缓冲区
	unsigned int  m_EBO;     // 索引缓冲区
	GLFWwindow*   m_pWindow;	
	Shaders       m_Shader;

	FrameBuffer   m_FBO;
	unsigned int  m_TextureId;
	unsigned int  m_DynamicTexture; 
};

