#include "../Core/Application.h"
#include "../Entity/Ground.h"
#include "../Entity/Triangle.h"
#include "iostream"
#include "../Entity/Box.h"
#include "BoxColorLighting.h"

#define APPLICTION "Lesson19-Lighting"

class LighingApp :public Application
{
 

	// 1.׼������
	virtual void Startup() 
	{	
		m_textureCity   = CreateTexture("textures/chongqing.jpg");
		m_textureGround = CreateTexture("textures/ground.jpg");
        
		m_triangle.Init();		
		m_box.Init();
		m_boxColor.Init();     

		m_ground.Init();
		m_ground.SetTexture(m_textureGround);

	}



	// 2.��Ⱦ����
	virtual void Render()
	{
         // glm::mat4 model(1.0f);
         // glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
         // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)m_winWidth / (GLfloat)m_winHeight, 0.1f, 100.0f);
        
         m_ground.Render(m_camera);
         m_triangle.Render(m_camera);

		 m_boxColor.Render(m_camera);
		 m_box.Render(m_camera);
       

		 printf("%d\r\n", m_franerNuber);


	}
	
	// 3.�ر�
	virtual void Shutdown()
	{
		// ɾ������
		glDeleteTextures(1,&m_textureCity);		
		glDeleteTextures(1,&m_textureGround);
	}

private: // ����	

	// ģ����
	Ground       m_ground;   // ����
	Triangle     m_triangle; // ������
	Box          m_box;      // ��ɫ����


	BoxColorLighting  m_boxColor; // ����ԭʼ��ɫ

	

   
	unsigned  m_textureCity   = 0;
	unsigned  m_textureGround = 0;	
	
};

int main()
{
	LighingApp lighingApp;	
	lighingApp.Initialize(1920 * 1, 1080 * 1, APPLICTION);
	lighingApp.Run();
}
