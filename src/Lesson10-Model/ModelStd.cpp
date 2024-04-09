#include"ModelStd.h"

ModelStd::ModelStd()
{
	m_VAO = 0;
	m_VBO = 0;
	m_EBO = 0;
	m_Size = 0;
}

ModelStd::~ModelStd()
{
	// ��������
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

bool ModelStd::Load(const char* fileName)  // ��������
{
	size_t  length = 0;
	char* xmlData = ReadFile(fileName, length);
	if (xmlData == 0)
	{
		printf("ModelStd.h����ȡʧ��...");
		return  false;
	}

	try
	{
		rapidxml::xml_document<>    doc;
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

		/// ��������
		faceRoot = meshNode->first_node("faceIndex");
		ParseFaceIndex(faceRoot);

		/// ������������
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

bool ModelStd::Load(const char* fileName, unsigned vao, unsigned vbo, unsigned ebo)  // ��������
{
	m_VAO = vao;
	m_VBO = vbo;
	m_EBO = ebo;
	size_t  length = 0;
	char* xmlData = ReadFile(fileName, length);
	if (xmlData == 0)
	{
		printf("ModelStd.h����ȡʧ��...");
		return  false;
	}

	try
	{
		rapidxml::xml_document<>    doc;
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

		/// ��������
		faceRoot = meshNode->first_node("faceIndex");
		ParseFaceIndex(faceRoot);

		/// ������������
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

// ������������Ϣ

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


	m_Size = arIndex.size();
	glGenVertexArrays(1, &m_VAO); // ��������������� VAO	
	glGenBuffers(1, &m_VBO);      // �������㻺����� VBO	
	glGenBuffers(1, &m_EBO);      // ��������������� EBO

	glBindVertexArray(m_VAO);     // �� VAO		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arIndex.size() * sizeof(short), &arIndex.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// ����������Ϣ

void ModelStd::ParseVertex(rapidxml::xml_node<>* vertRoot)
{
	std::vector<Vertex>         arVert;
	rapidxml::xml_attribute<>* attrSize = vertRoot->first_attribute("size");
	rapidxml::xml_node<>* vertNode = vertRoot->first_node();
	for (; vertNode; vertNode = vertNode->next_sibling())
	{
		const char* pzVert = vertNode->value();
		Vertex      vertex;
		sscanf(pzVert, "%f %f %f %f %f %f %f %f", &vertex.x, &vertex.y, &vertex.z, &vertex.u, &vertex.v, &vertex.nx, &vertex.ny, &vertex.nz);
		arVert.push_back(vertex);
	}


	glBindVertexArray(m_VAO);     // �� VAO
	// �� VBO ���������
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, arVert.size() * sizeof(Vertex), &arVert.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

/**
*   ���ƺ���
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

void ModelStd::Render(float fElapsed, ThirdCamera& camera, Shader_DirLight& shader)
{

	glm::mat4 mv;			
	// ����ģ�;���
	glm::mat4 model      = glm::mat4(1.0f);          // ��ʼ��Ϊ��λ����	
	glm::mat4 view       = camera.GetView();         // ���ù۲����			
	glm::mat4 projection = camera.GetProject();      // ����ͶӰ����
	mv =   view * model;	



	shader.Begin();
	{
		// ÿ�λ�֮ǰ��	
		glBindVertexArray(m_VAO);     // �� VAO	
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		glm::mat3  matNor(1); // ���� 
		matrix4ToMatrix3(matNor, mv);
		//glUniform1i(shader.m_Texture, 0);
		//! ���Ƶ���
		glUniformMatrix4fv(shader.m_Mv, 1, false, (const GLfloat*)&mv);
		glUniformMatrix4fv(shader.m_Project, 1, false, (const GLfloat*)&projection);
		glUniformMatrix3fv(shader.m_NormalMat, 1, false, (const GLfloat*)&matNor);

		glUniform3f(shader.m_AmbientColor, 0.2f, 0.2f, 0.2f);
		glUniform3f(shader.m_LightDirection, 0.0f, 1.0f, 0.0f);
		glUniform3f(shader.m_DiffuseColor, 0.3f, 0.3f, 0.3f);

		// ���ö�������ָ��
		glVertexAttribPointer(shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
		glVertexAttribPointer(shader.m_Uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
		glVertexAttribPointer(shader.m_Normal, 3, GL_FLOAT, false, sizeof(Vertex), (void*)20);
		glVertexAttribPointer(shader.m_Position, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	
		
		
		glDrawElements(GL_TRIANGLES, m_Size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	shader.End();
	
}

// ��ȡ�ļ�
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
