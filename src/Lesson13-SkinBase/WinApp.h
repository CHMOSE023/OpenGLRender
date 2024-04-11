#pragma once
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Timestamp.h"
#include "SkinBase.h"
#include "Timestamp.h"

class WinApp
{
public:
	WinApp();
	~WinApp();
    void Initialize(int width, int height, const char* title);  // 1.��ʼ��
	void Run();
private:
    void Startup();             // 1.׼������
    void Render();              // 2.��Ⱦ����
    void Shutdown()const;       // 3.�ر�
private:

	typedef struct Vertex       //  ����һ���������Ϣ
	{
		float r, g, b, a;   	//! ��ɫ	
		float x, y, z;          //! λ��		
		float weights[2];       //! Ӱ���		
		short matrixIndices[2]; //! ���������	
		short numBones;         //! Ӱ����������Ĺ�ͷ����
	}Vertex;

	Vertex m_QuadVertices[12] =
	{
		    //       ��ɫ                λ��            Ӱ���     ���������   Ӱ���ͷ����
		{   1.0f,1.0f,0.0f,1.0f,   -1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     }, // ��ɫ
		{   1.0f,1.0f,0.0f,1.0f,    1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     },
		{   1.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   1.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },

		{   0.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // ��ɫ
		{   0.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,1.0f,0.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,1.0f,0.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },

		{   0.0f,0.0f,1.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // ��ɫ
		{   0.0f,0.0f,1.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,0.0f,1.0f,1.0f,    1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     },
		{   0.0f,0.0f,1.0f,1.0f,   -1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     }

	};

	typedef struct  BoneVertex   	// ������������
	{
		float   x, y, z;
		float   r, g, b, a;
	}BoneVertex;

	// ���ƹ���ʹ�õ��Ķ�������
	BoneVertex   m_ArBone[14] =
	{
		{ 0.0f, 0.0f, 0.0f,  0,0,1,1},
		{-0.2f, 0.2f,-0.2f,  0,0,1,1},
		{ 0.2f, 0.2f,-0.2f,  0,0,1,1},
		{ 0.0f, 3.0f, 0.0f,  0,0,1,1},
		{-0.2f, 0.2f,-0.2f,  0,0,1,1},
		{-0.2f, 0.2f, 0.2f,  0,0,1,1},
		{ 0.0f, 0.0f, 0.0f,  0,0,1,1},
		{ 0.2f, 0.2f,-0.2f,  0,0,1,1},
		{ 0.2f, 0.2f, 0.2f,  0,0,1,1},
		{ 0.0f, 0.0f, 0.0f,  0,0,1,1},
		{-0.2f, 0.2f, 0.2f,  0,0,1,1},
		{ 0.0f, 3.0f, 0.0f,  0,0,1,1},
		{ 0.2f, 0.2f, 0.2f,  0,0,1,1},
		{-0.2f, 0.2f, 0.2f,  0,0,1,1},
	};


private:
	int              m_Width;
	int	             m_Height;
	GLFWwindow*      m_pWindow;	
				    
	GLuint           m_VAOS[2];
	GLuint           m_VboArBone;
	GLuint           m_VboQuad;
	Timestamp        m_Times;
	Shader_P3_C4_T2  m_Shader;
	Timestamp        m_Timestamp;
	SkinBase         m_SkinBase;

	float            m_TimeElpased; // �ۼ���ʱ glfwTime()
	glm::mat4        m_matrixToRenderBone[2];

};

