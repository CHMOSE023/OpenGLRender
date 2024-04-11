#include <glad/glad.h>
#include "WinApp.h"
#include <stdlib.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#pragma region glfw窗口及事件处理
WinApp::WinApp()
{	
}

WinApp::~WinApp()
{	
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void WinApp::Initialize(int width, int height, const char* title)
{	
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGL();
	glfwSwapInterval(1);     // 垂直同步打开1 关闭0	
	glEnable(GL_DEPTH_TEST); // 开启深度测试
}

void WinApp::Run()
{
	Startup();    // 1.渲染前准备工作
	double curTime = 0;
	int num = 0;
	while (!glfwWindowShouldClose(m_pWindow))
	{
		float   elapseTime = (float)m_Timestamp.GetElapsedSecond();		
		m_TimeElpased += elapseTime; // 累计用时

		// 计算帧率
		curTime += m_Times.GetElapsedSecond();
		if (curTime >= 1.0f)
		{
			printf("当前帧率：%d\r", num);
			num = 0; curTime = 0;
		}
		else
		{
			num++;
		}
		m_Times.Update();
		glfwGetFramebufferSize(m_pWindow, &m_Width, &m_Height);

		glViewport(0, 0, m_Width, m_Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		Render(); // 2.开始渲染

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents(); // 检查窗口当前是否有事件发生
	}
	Shutdown();   // 3.结束渲染
}
#pragma endregion 

void WinApp::Startup() 
{
	// 1.准备Shader
	m_Shader.Initialize(); 

	// 2.准备数据	
	m_TimeElpased = 0;	

	m_SkinBase.m_KeyFrame[0].m_Bone[0] = glm::mat4(1);
	m_SkinBase.m_KeyFrame[0].m_Bone[1] = glm::mat4(1);

	m_SkinBase.m_KeyFrame[1].m_Bone[0] = glm::mat4(1);
	m_SkinBase.m_KeyFrame[1].m_Bone[1] = glm::mat4(1);

	glm::mat4 rotationMatrixY(1);
	glm::mat4 rotationMatrixZ(1);
	rotationMatrixY = glm::rotate(glm::mat4(1), glm::radians( 60.0f), glm::vec3(0, 1, 0)); // glm::radians( 60.0f)
	rotationMatrixZ = glm::rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0, 0, 1)); // glm::radians(-60.0f)

	m_SkinBase.m_KeyFrame[1].m_Bone[1] = rotationMatrixY * rotationMatrixZ;

	
	// 创建顶点缓冲区
	glGenVertexArrays(2, m_VAOS);
	// 线框顶点
	glBindVertexArray(m_VAOS[0]);	
	glGenBuffers(1, &m_VboQuad);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_QuadVertices), m_QuadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(m_Shader.m_Color, 4, GL_FLOAT, false, sizeof(Vertex), (void*)0);	
	glEnableVertexAttribArray(m_Shader.m_Position);
	glEnableVertexAttribArray(m_Shader.m_Color);

	// 骨骼顶点	
	glBindVertexArray(m_VAOS[1]);		
	glGenBuffers(1, &m_VboArBone);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboArBone);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_ArBone), m_ArBone, GL_STATIC_DRAW);
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, false, sizeof(BoneVertex), (void*)0);
	glVertexAttribPointer(m_Shader.m_Color, 4, GL_FLOAT, false, sizeof(BoneVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_Shader.m_Position);
	glEnableVertexAttribArray(m_Shader.m_Color);
	
}


void WinApp::Render()
{	
	Frame frame = {};                           // 帧矩阵插值	
	m_SkinBase.CalcFrame(glfwGetTime(), frame); // 根据关键帧计算出来新的骨骼位置
	 
	// 计算骨骼动画
	{	
	    glm::mat4 offsetMatrix_toBoneEnd       = glm::translate(glm::vec3(0.0f, 3.0f, 0.0f));
	    glm::mat4 offsetMatrix_backFromBoneEnd = glm::translate(glm::vec3(0.0f, -3.0f, 0.0f));
	    
	    m_matrixToRenderBone[0] = frame.m_Bone[0];
	    glm::mat4 temp          = frame.m_Bone[1];
	    
	    frame.m_Bone[1]         = offsetMatrix_toBoneEnd * frame.m_Bone[1];
	    m_matrixToRenderBone[1] = offsetMatrix_toBoneEnd * temp;
	    frame.m_Bone[1]         = frame.m_Bone[1] * offsetMatrix_backFromBoneEnd;	    
	}

	// 计算线框动画
	Vertex  calQuadVertices[12] = {};
	memcpy(calQuadVertices, m_QuadVertices, sizeof(m_QuadVertices));

	for (int i = 0; i < 12; ++i)
	{
		glm::vec3    vec(0, 0, 0);
		glm::vec3    vecSrc(m_QuadVertices[i].x, m_QuadVertices[i].y, m_QuadVertices[i].z);
		for (int x = 0; x < calQuadVertices[i].numBones; ++x)
		{			
			glm::vec3  temp = frame.m_Bone[m_QuadVertices[i].matrixIndices[x]] * glm::vec4(vecSrc, 1.0); //! 计算位置			
			vec += temp * m_QuadVertices[i].weights[x]; //! 计算权重位置
		}

		calQuadVertices[i].x = vec.x;
		calQuadVertices[i].y = vec.y;
		calQuadVertices[i].z = vec.z;
	}
	
	 glBindBuffer(GL_ARRAY_BUFFER, m_VboQuad);
	 glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(calQuadVertices), calQuadVertices);  // 更新数据	 


	 glm::mat4 matProj = glm::perspective(45.0f, (GLfloat)m_Width / (GLfloat)m_Height, 0.1f, 100.0f);
	 glm::mat4 matModel(1);
	 glm::mat4 matView(1);
	 matModel = glm::translate(matModel, glm::vec3(0, -3, -10));
	 glm::mat4 mvp = matProj * matModel * matView;
	

	 // 使用shader
	 m_Shader.Begin();
	 {
		 glBindVertexArray(m_VAOS[0]); // 顶点数组1
		 glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, glm::value_ptr(mvp));
		 for (int i = 0; i < 3; ++i)
		 {
			 glDrawArrays(GL_LINE_LOOP, i * 4, 4);
		 }

		 glBindVertexArray(m_VAOS[1]); // 顶点数组2
		 glm::mat4 matBone0 = matProj * matModel * m_matrixToRenderBone[0];
		 glUniformMatrix4fv(m_Shader.m_MVP, 1, false, glm::value_ptr(matBone0));
		 glDrawArrays(GL_LINE_STRIP, 0, 14);

		 glm::mat4 matBone1 = matProj * matModel * m_matrixToRenderBone[1];
		 glUniformMatrix4fv(m_Shader.m_MVP, 1, false, glm::value_ptr(matBone1));
		 glDrawArrays(GL_LINE_STRIP, 0, 14);
	 }

	m_Shader.End();	
}

void WinApp::Shutdown()const
{
	glDeleteVertexArrays(2, m_VAOS);	
	glDeleteBuffers(1, &m_VboArBone);
	glDeleteBuffers(1, &m_VboQuad);
}
