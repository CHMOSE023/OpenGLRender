#include <glad/glad.h>
#include "WinApp.h"
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


WinApp::WinApp()
{	
}

WinApp::~WinApp()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void WinApp::ErrorCallback(int error, const char* description)
{
}

void WinApp::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void WinApp::Initialize(int width, int height,const char*title)
{
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow=  glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(m_pWindow, KeyCallback);

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGL();
	glfwSwapInterval(1);

	// 初始化 shader
	m_Shader.Initialize();
	// 加载纹理
	LoadTexture("textures/animation.png");
		

	Vertex  vertices[6] =
	{
		//       顶点                 UV                
	   {  -1.0f,-1.0f, 1.0f ,   0.0f,0.0f  },
	   {   1.0f,-1.0f, 1.0f ,   1.0f,0.0f  },
	   {   1.0f, 1.0f, 1.0f ,   1.0f,1.0f  },
	
	   {  -1.0f,-1.0f, 1.0f ,   0.0f,0.0f  },
	   {   1.0f, 1.0f, 1.0f ,   1.0f,1.0f  },
	   {  -1.0f, 1.0f, 1.0f ,   0.0f,1.0f  },
	};
	
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(m_Shader.m_Position);
	glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(m_Shader.m_UV);
	glVertexAttribPointer(m_Shader.m_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// 启用混合
	glEnable(GL_BLEND);
	// 混合方程
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void WinApp::Run()
{	
	
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwGetFramebufferSize(m_pWindow, &m_Width, &m_Height);
		glViewport(0, 0, m_Width, m_Height);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		Render();

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}
double m_LastFrameTime;
void WinApp::Render()
{
	double currentFrameTime = glfwGetTime();                // 获取当前帧的时间
	double deltaTime = currentFrameTime - m_LastFrameTime;  // 计算帧间隔	
	m_LastFrameTime = currentFrameTime;                     // 更新上一帧时间

	const float ratio = m_Width / (float)m_Height;
	mat4x4 m, p, mvp;
	mat4x4_identity(m);
	//mat4x4_rotate_Z(m, m, (float)glfwGetTime());
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);
	
	int     row = 4;
	int     col = 4;
	static  float   curFrame = 0.0f;

	float   tm = deltaTime * 16;

	curFrame += tm;
	if (curFrame > 16)
	{
		curFrame = 0;
	}

	float   fR = 1.0f /row;
	float   fC = 1.0f / col;

	//! 计算当前行
	int     cR = int(curFrame / col);
	//! 计算当前列
	int     cC = int(curFrame - cR * col);


	Vertex  position[6] =
	{
		//       顶点                 UV                
	   {  -1.0f,-1.0f, 1.0f ,   0.0f,0.0f  },
	   {   1.0f,-1.0f, 1.0f ,   1.0f,0.0f  },
	   {   1.0f, 1.0f, 1.0f ,   1.0f,1.0f  },

	   {  -1.0f,-1.0f, 1.0f ,   0.0f,0.0f  },
	   {   1.0f, 1.0f, 1.0f ,   1.0f,1.0f  },
	   {  -1.0f, 1.0f, 1.0f ,   0.0f,1.0f  },
	};


	for (int i = 0; i < 6; ++i)
	{		

		//! 对坐标进行缩放
		position[i].u *= fR;
		position[i].v *= fC;

		//! 对坐标进行平移
		position[i].u += cC * fC;
		position[i].v += cR * fR;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0,sizeof(position), position);

	
	// 使用shader
	m_Shader.Begin();

	glUniformMatrix4fv(m_Shader.m_MVP, 1, GL_FALSE, (const GLfloat*)&mvp);	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_Shader.End();
	
}

void WinApp::LoadTexture(const char* fileName)
{
	//unsigned int texture;
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 翻转图像
	stbi_set_flip_vertically_on_load(true);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels==3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}


	}
	else
	{
		printf("加载失败\n");
	}
	stbi_image_free(data);


}

