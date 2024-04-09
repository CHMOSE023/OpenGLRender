#pragma once
#include "rapidxml.hpp"
#include <stdio.h>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "ThirdCamera.h"
#include "Shader_DirLight.h"

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

	ModelStd();;
	~ModelStd();;
public:
	bool Load(const char* fileName);
	bool Load(const char* fileName, unsigned vao,unsigned vbo, unsigned ebo);

	// 解析面索引信息
	void ParseFaceIndex(rapidxml::xml_node<>* faceRoot);
	// 解析顶点信息
	void ParseVertex(rapidxml::xml_node<>* vertRoot);
	// 绘制函数
	void matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src);
	void Render(float fElapsed, ThirdCamera& camera, Shader_DirLight& shader);

protected:
	// 读取文件
	char* ReadFile(const char* fileName, size_t& size);

public:
	unsigned m_VAO;		// 创建顶点数组对象 VAO	
	unsigned m_VBO;		// 创建顶点缓冲对象 VBO	
	unsigned m_EBO;		// 创建索引缓冲对象 EBO
	unsigned m_Size;


};

