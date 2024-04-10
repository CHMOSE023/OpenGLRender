#pragma once
#include "rapidxml.hpp"
#include <stdio.h>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "ThirdCamera.h"
#include "Shader_DirLight.h"
#include <vector>

class ModelStd
{
public :
	struct  Vertex
	{
		float x, y, z;
		float u, v;
		float nx, ny, nz;
	};
public:

	ModelStd();	
	~ModelStd();
public:
	bool Load(const char* fileName);
	bool LoadKeyFrame(const char* fileName);
	// ������������Ϣ
	void ParseFaceIndex(rapidxml::xml_node<>* faceRoot);
	// ����������Ϣ
	void ParseVertex(rapidxml::xml_node<>* vertRoot);
	// ���ƺ���
	void Render(float fElapsed, ThirdCamera& camera, Shader_DirLight& shader);
	void SetShader(Shader_DirLight shader); // SetShaderĿ�ģ��ύ����ʹ�õ�shader�洢�����У� ParseVertex �������������ݹ�����shader�������У����Ч�ʡ�
	
protected:
	// ��ȡ�ļ�
	char* ReadFile(const char* fileName, size_t& size);
	void matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src);
public:
	unsigned m_VAO;		// ��������������� VAO	
	unsigned m_VBO;		// �������㻺����� VBO	
	unsigned m_EBO;		// ��������������� EBO
	unsigned m_Size;

	Shader_DirLight  m_Shader;       // 
	float            m_TimeIndex;    // ʱ��֡

	std::vector<glm::mat4> m_KeyMat; // �ؼ�֡����

};
