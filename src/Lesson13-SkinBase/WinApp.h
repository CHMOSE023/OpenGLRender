#pragma once
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Timestamp.h"
#include "SkinBase.h"

// ����һ���������Ϣ
typedef struct Vertex
{
    //! ��ɫ
    float r, g, b, a;
    //! λ��
    float x, y, z;
    //! Ӱ���
    float weights[2];
    //! ���������
    short matrixIndices[2];
    //! Ӱ����������Ĺ�ͷ����
    short numBones;
}Vertex;


// ������������
typedef struct  BoneVertex
{
    float   x, y, z;
    float   r, g, b, a;
}BoneVertex;


class WinApp
{
public:
	WinApp();
	~WinApp();
    void Initialize(int width, int height, const char* title);  // 1.��ʼ��
	void Run();

private:
    void Startup();     // 1.׼������
    void Render();      // 2.��Ⱦ����
    void Shutdown();   // 3.�ر�

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
private:
    // ��������
   // Vertex m_QuadVertices[12] =
   // {
   //     //       ��ɫ                λ��            Ӱ���     ���������   Ӱ���ͷ����
   //     {   1.0f,1.0f,0.0f,1.0f,   -1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     }, // ��ɫ
   //     {   1.0f,1.0f,0.0f,1.0f,    1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     },
   //     {   1.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   1.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //                                                                                      
   //     {   0.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // ��ɫ
   //     {   0.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2}    ,
   //     {   0.0f,1.0f,0.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   0.0f,1.0f,0.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //                                                                                      
   //     {   0.0f,0.0f,1.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // ��ɫ
   //     {   0.0f,0.0f,1.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   0.0f,0.0f,1.0f,1.0f,    1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     },
   //     {   0.0f,0.0f,1.0f,1.0f,   -1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     }
   // };

private:
    // ���ƹ���ʹ�õ��Ķ�������
    BoneVertex   m_ArBone[14] =
    {
        {0.0f, 0.0f, 0.0f,0,0,1,1},
        {-0.2f, 0.2f,-0.2f,0,0,1,1},
        {0.2f, 0.2f,-0.2f,0,0,1,1},
        {0.0f, 3.0f, 0.0f,0,0,1,1},
        {-0.2f, 0.2f,-0.2f,0,0,1,1},
        {-0.2f, 0.2f, 0.2f,0,0,1,1},
        {0.0f, 0.0f, 0.0f,0,0,1,1},
        {0.2f, 0.2f,-0.2f,0,0,1,1},
        {0.2f, 0.2f, 0.2f,0,0,1,1},
        {0.0f, 0.0f, 0.0f,0,0,1,1},
        {-0.2f, 0.2f, 0.2f,0,0,1,1},
        {0.0f, 3.0f, 0.0f,0,0,1,1},
        {0.2f, 0.2f, 0.2f,0,0,1,1},
        {-0.2f, 0.2f, 0.2f,0,0,1,1},
    };

private:
	int              m_Width;
	int	             m_Height;
	GLFWwindow*      m_pWindow;	
				    
	GLuint           m_VAO;
	GLuint           m_VBO; 
	Timestamp        m_Times;
	Shader_P3_C4_T2  m_Shader;

};

