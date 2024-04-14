#include"ModelStd.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Frustum.h"
ModelStd::ModelStd()
{
	m_VAO = 0;
	m_VBO = 0;
	m_EBO = 0;
	m_size = 0;
}

ModelStd::~ModelStd()
{
	// 清理数据
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

bool ModelStd::Load(const char* fileName)  // 加载数据
{
	size_t  length = 0;
	char* xmlData = ReadFile(fileName, length);
	if (xmlData == 0)
	{
		printf("ModelStd.h：读取失败...");
		return  false;
	}

	try
	{
		rapidxml::xml_document<>    doc ;
		rapidxml::xml_node<>* rootNode = 0;
		rapidxml::xml_node<>* meshNode = 0;
		rapidxml::xml_node<>* faceRoot = 0;
		rapidxml::xml_node<>* vertRoot = 0;
		doc.parse<0>(xmlData);
		rootNode = doc.first_node("MeshRoot");
		if (rootNode == 0)
		{
			return  false;
		}
		meshNode = rootNode->first_node();
		if (meshNode == 0)
		{
			return  false;
		}

		/// 解析顶点
		faceRoot = meshNode->first_node("faceIndex");
		ParseFaceIndex(faceRoot);

		/// 解析顶点数据
		vertRoot = meshNode->first_node("vertex");
		ParseVertex(vertRoot);

		delete[] xmlData;
		return  true;
	}
	catch (...)
	{
		return  false;
	}

}

// 解析面索引信息
void ModelStd::ParseFaceIndex(rapidxml::xml_node<>* faceRoot)
{
	std::vector<short>          arIndex;
	rapidxml::xml_node<>* pFaceIndex = faceRoot->first_node();
	for (; pFaceIndex; pFaceIndex = pFaceIndex->next_sibling())
	{
		const char* pzFace = pFaceIndex->value();
		int     a, b, c;
		sscanf(pzFace, "%d %d %d", &a, &b, &c);
		arIndex.push_back(short(a));
		arIndex.push_back(short(b));
		arIndex.push_back(short(c));
	}

	m_size = arIndex.size();
	glBindVertexArray(m_VAO);     // 绑定 VAO		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arIndex.size() * sizeof(short), &arIndex.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// 解析顶点信息
void ModelStd::ParseVertex(rapidxml::xml_node<>* vertRoot)
{
	std::vector<Vertex>         arVert;
	std::vector<glm::vec3>      tempVert;
	rapidxml::xml_attribute<>*  attrSize = vertRoot->first_attribute("size");
	rapidxml::xml_node<>*       vertNode = vertRoot->first_node();

	for (; vertNode; vertNode = vertNode->next_sibling())
	{
		const char* pzVert = vertNode->value();
		Vertex      vertex;
	  	sscanf(pzVert, "%f %f %f %f %f %f %f %f", &vertex.x, &vertex.y, &vertex.z, &vertex.u, &vertex.v, &vertex.nx, &vertex.ny, &vertex.nz);
		arVert.push_back(vertex);

		glm::vec3 tempVec3(vertex.x, vertex.y, vertex.z);

		tempVert.push_back(tempVec3);
	}

	glm::vec3 originalMin(-1.0f, -1.0f, -1.0f);
	glm::vec3 originalMax(1.0f, 1.0f, 1.0f);

	// 初始化包围盒 	
	m_aabb = AABB::FromPointCloud(tempVert);
	//_aabb.setExtents(real3(FLT_MAX, FLT_MAX, FLT_MAX), real3(-FLT_MAX, -FLT_MAX, -FLT_MAX));

	glBindVertexArray(m_VAO);     // 绑定 VAO
	// 绑定 VBO 并填充数据
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, arVert.size() * sizeof(Vertex), &arVert.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(m_shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(m_shader.m_Uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
	glVertexAttribPointer(m_shader.m_Normal, 3, GL_FLOAT, false, sizeof(Vertex), (void*)20);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

/**
*   绘制函数
*/

void ModelStd::matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src)
{
	t[0][0] = src[0][0];
	t[0][1] = src[0][1];
	t[0][2] = src[0][2];
	t[1][0] = src[1][0];
	t[1][1] = src[1][1];
	t[1][2] = src[1][2];
	t[2][0] = src[2][0];
	t[2][1] = src[2][1];
	t[2][2] = src[2][2];
}


void ModelStd::Render( ThirdCamera& camera, const glm::mat4& model)
{
	
	glm::mat4 mv;			
	// 设置模型矩阵
	glm::mat4 modelMat      = model;                // node中模型位置	
	glm::mat4 viewMat       = camera.GetView();     // 设置观察矩阵		
	glm::mat4 projectionMat = camera.GetProject();  // 设置投影矩阵
	
	mv = viewMat * modelMat;

	glm::mat3  matNor(1); // 法线 
	matrix4ToMatrix3(matNor, mv);

	m_shader.Begin();
	{	

		glUniform1i(m_shader.m_Texture, 0);
		//! 绘制地面
		glUniformMatrix4fv(m_shader.m_Mv, 1, false, (const GLfloat*)&mv);
		glUniformMatrix4fv(m_shader.m_Project, 1, false, (const GLfloat*)&projectionMat);
		glUniformMatrix3fv(m_shader.m_NormalMat, 1, false, (const GLfloat*)&matNor);
		glUniform3f(m_shader.m_AmbientColor, 0.2f, 0.2f, 0.2f);
		glUniform3f(m_shader.m_LightDirection, 0.0f, 1.0f, 0.0f);
		glUniform3f(m_shader.m_DiffuseColor, 0.3f, 0.3f, 0.3f);

		// 每次会之前绑定	
		glBindVertexArray(m_VAO);     // 绑定 VAO	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}

	m_shader.End();
}

void ModelStd::SetShader(Shader_DirLight shader)
{
	m_shader = shader;
	glGenVertexArrays(1, &m_VAO); // 创建顶点数组对象 VAO	
	glGenBuffers(1, &m_VBO);      // 创建顶点缓冲对象 VBO	
	glGenBuffers(1, &m_EBO);      // 创建索引缓冲对象 EBO
}

// 读取文件
char* ModelStd::ReadFile(const char* fileName, size_t& size)
{
	FILE* file = fopen(fileName, "rb");
	if (file == 0)
	{
		return  0;
	}
	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buffer = new char[length + 1];
	fread(buffer, 1, length, file);
	buffer[length] = 0;
	size = length;
	fclose(file);
	return  buffer;

}
