#pragma once
#include "Program_P2_C3.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Timestamp.h"

class WinApp
{
public:
	WinApp();
	~WinApp();
    void Initialize(int width, int height, const char* title);  // 1.��ʼ��
	void Run();

private:
    void Startup();         // 1.׼������
    void Render();          // 2.��Ⱦ����
    void Shutdown()const;   // 3.�ر�

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);	

private:
	int              m_Width;
	int	             m_Height;
	GLFWwindow*      m_pWindow;	
				    
	GLuint           m_VAO;
	GLuint           m_VBO; 
	Timestamp        m_Times;
	PROGRAM_P2_C3    m_Shader;

};

