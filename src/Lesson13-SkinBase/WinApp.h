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
    void Initialize(int width, int height, const char* title);  // 1.初始化
	void Run();
private:
    void Startup();             // 1.准备数据
    void Render();              // 2.渲染数据
    void Shutdown()const;       // 3.关闭
private:

	typedef struct Vertex       //  描述一个顶点的信息
	{
		float r, g, b, a;   	//! 颜色	
		float x, y, z;          //! 位置		
		float weights[2];       //! 影响度		
		short matrixIndices[2]; //! 矩阵的索引	
		short numBones;         //! 影响整个定点的骨头个数
	}Vertex;

	Vertex m_QuadVertices[12] =
	{
		    //       颜色                位置            影响度     矩阵的索引   影响骨头个数
		{   1.0f,1.0f,0.0f,1.0f,   -1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     }, // 蓝色
		{   1.0f,1.0f,0.0f,1.0f,    1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     },
		{   1.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   1.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },

		{   0.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // 绿色
		{   0.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,1.0f,0.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,1.0f,0.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },

		{   0.0f,0.0f,1.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // 黄色
		{   0.0f,0.0f,1.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
		{   0.0f,0.0f,1.0f,1.0f,    1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     },
		{   0.0f,0.0f,1.0f,1.0f,   -1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     }

	};

	typedef struct  BoneVertex   	// 骨骼顶点数据
	{
		float   x, y, z;
		float   r, g, b, a;
	}BoneVertex;

	// 绘制骨骼使用到的顶点数据
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

	float            m_TimeElpased; // 累计用时 glfwTime()
	glm::mat4        m_matrixToRenderBone[2];

};

