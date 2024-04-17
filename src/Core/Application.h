#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TimeStamp.h"
#include "Camera.h"
class Application
{
public:
	Application();
	virtual ~Application();
	virtual void  Initialize(int width, int height, const char* title);  // 1.��ʼ��
	virtual void  Run();	  
	virtual void  Startup();        // 1.׼������
	virtual void  Render();         // 2.��Ⱦ����
	virtual void  Shutdown();       // 3.�ر�

private:
	// ϵͳ�ص�����
	static void  ErrorCallback(int error, const char* description);
	static void  KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void  MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void  CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void  WindowSizeCallback(GLFWwindow* window, int width, int height);
	static void  ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static Application* GetWindow(GLFWwindow* window);
	glm::dvec3 CalcIntersectPoint(Ray& ray); // �����ϵ�Ŀ���
protected:
	unsigned     CreateTexture(const char* fileName);

protected:
	int           m_winWidth;
	int	          m_winHeight;
	GLFWwindow*   m_pWindow;	
	TimeStamp     m_timeStamp;     // ʱ���
	Camera        m_camera;        // ���

	double        m_elapsedTime;   // ����ʱ��
	double        m_frameTime;     // ��¼��һ֡��ʱ��	,һ��SwapBuffers��ʱ		
	unsigned int  m_franerNuber;   // ֡��
	double        m_xPos;		   // ���x
	double        m_yPos;		   // ���y

private:
	bool          m_bRightFlg;	   // ����Ҽ����� 
	glm::dvec2    m_rightPosition; // ����Ҽ�����λ��
				  
	bool          m_bLeftFlg;	   // ������������ 
	glm::dvec2    m_leftPosition;  // ����������λ��
	
};

