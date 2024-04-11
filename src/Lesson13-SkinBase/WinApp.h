#pragma once
#include "Shader_P3_C4_T2.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Timestamp.h"
#include "SkinBase.h"

// 描述一个顶点的信息
typedef struct Vertex
{
    //! 颜色
    float r, g, b, a;
    //! 位置
    float x, y, z;
    //! 影响度
    float weights[2];
    //! 矩阵的索引
    short matrixIndices[2];
    //! 影响整个定点的骨头个数
    short numBones;
}Vertex;


// 骨骼顶点数据
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
    void Initialize(int width, int height, const char* title);  // 1.初始化
	void Run();

private:
    void Startup();     // 1.准备数据
    void Render();      // 2.渲染数据
    void Shutdown();   // 3.关闭

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
private:
    // 顶点数据
   // Vertex m_QuadVertices[12] =
   // {
   //     //       颜色                位置            影响度     矩阵的索引   影响骨头个数
   //     {   1.0f,1.0f,0.0f,1.0f,   -1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     }, // 蓝色
   //     {   1.0f,1.0f,0.0f,1.0f,    1.0f,0.0f,0.0f,  1.0f,0.0f,    0,0,            1     },
   //     {   1.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   1.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //                                                                                      
   //     {   0.0f,1.0f,0.0f,1.0f,   -1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // 绿色
   //     {   0.0f,1.0f,0.0f,1.0f,    1.0f,2.0f,0.0f,  0.5f,0.5f,    0,1,            2}    ,
   //     {   0.0f,1.0f,0.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   0.0f,1.0f,0.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //                                                                                      
   //     {   0.0f,0.0f,1.0f,1.0f,   -1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     }, // 黄色
   //     {   0.0f,0.0f,1.0f,1.0f,    1.0f,4.0f,0.0f,  0.5f,0.5f,    0,1,            2     },
   //     {   0.0f,0.0f,1.0f,1.0f,    1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     },
   //     {   0.0f,0.0f,1.0f,1.0f,   -1.0f,6.0f,0.0f,  1.0f,0.0f,    1,0,            1     }
   // };

private:
    // 绘制骨骼使用到的顶点数据
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

