#include "ModelStd.h"

ModelStd::ModelStd()
{
    m_times = 0;
}

ModelStd::~ModelStd()
{
    Shutdown();  //��������   
}

void ModelStd::Load(const char* meshName, const char* skinName)
{
    LoadMesh(meshName); // xml
    LoadSkin(skinName); // ������
}

// ����������Ϣ
void ModelStd::LoadSkin(const char* fileName)
{
    FILE* pFile = fopen(fileName, "rb");
    if (pFile == NULL)
    {
        return;
    }
    fseek(pFile, 0, SEEK_END);
    int	iSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    CHUNK	chunk;
    while (fread(&chunk, sizeof(CHUNK), 1, pFile))
    {
        switch (chunk.id)
        {
        case ECHUNK_MAGIC:
        {
            char   data[4];
            char   magic[4] = { 'C','E','L','L' };
            // fseek(pFile, 0x10, SEEK_SET);
            fread(data, sizeof(data) ,1 , pFile);
            if (memcmp(data, magic, 4) != 0)
            {
                fclose(pFile);
                return;
            }
            else
            {   
                fseek(pFile, (long)chunk.end, SEEK_SET);
            }
           
        }
        break;
        case ECHUNK_VERSION:
        {
            int	iVersion;
            fread(&iVersion, sizeof(int), 1, pFile);
            fseek(pFile, (long)chunk.end, SEEK_SET);
        }
        break;
        case ECHUNK_SKIN_BONE:       // ��ͷ��ÿ����ͷһ������
        {
            int	iSize = chunk.length / sizeof(glm::mat4(1));
            m_arBone.resize(iSize);
            fread(&m_arBone[0], chunk.length, 1, pFile);
        }
        break;
        case ECHUNK_SKIN_WEIGHT_LIST:// Ȩ����Ϣ��
        {

            m_arWeight.resize(m_arVertex.size());
            int	iIndex = 0;
          
            // 
            while (ftell(pFile) < (long)chunk.end)
            {                
                //!	��weight
                CHUNK	cTemp;
                fread(&cTemp, sizeof(CHUNK), 1, pFile);
                int 	iSize = cTemp.length / sizeof(Weight);
                m_arWeight[iIndex].resize(iSize);
                switch (cTemp.id)
                {
                case ECHUNK_SKIN_WEIGHT:
                {
                    fread(&m_arWeight[iIndex][0], cTemp.length, 1, pFile);
                    ++iIndex;
                }
                break;
                }
            }
        }
        break;
        case ECHUNK_SKIN_ANIMATION:  // ������Ϣ��ÿ֡һ������
        {
            while (ftell(pFile) < (long)chunk.end)
            {
                CHUNK	cTemp;
                fread(&cTemp, sizeof(CHUNK), 1, pFile);
                switch (cTemp.id)
                {
                case ECHUNK_SKIN_ANIMATION_NAME:
                {
                    std::string	strName = ReadString(pFile, cTemp);
                }
                break;
                case ECHUNK_SKIN_ANIMATION_FRAME:
                {
                    arraybone	arMatrix;
                    int 	iSize = cTemp.length / sizeof(glm::mat4(1)); //!!!
                    arMatrix.resize(iSize);
                    fread(&arMatrix[0], cTemp.length, 1, pFile);
                    m_arFrame.push_back(arMatrix);
                }
                break;
                }
            }
        }
        break;
        }
    }
    fclose(pFile);
    return;
}

std::string ModelStd::ReadString(FILE* _pFile, const CHUNK& _chunk)
{
    std::string	strText;
    strText.resize(_chunk.length + 1);
    fread(&strText[0], _chunk.length, 1, _pFile);
    return	strText;
}

// ����������
bool ModelStd::LoadMesh(const char* fileName)
{
    /// ���ļ�
    size_t  length = 0;
    char* xmlData = ReadFile(fileName, length);
    if (xmlData == 0)
    {
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

        // ����������
        faceRoot = meshNode->first_node("faceIndex");
        ParseFaceIndex(faceRoot);
        vertRoot = meshNode->first_node("vertex");
        // ������������
        ParseVertex(vertRoot);

        delete[] xmlData;
        return  true;
    }
    catch (...)
    {
        return  false;
    }   
}

// ��������Ϣ 
void ModelStd::ParseFaceIndex(rapidxml::xml_node<>* faceRoot)
{
   
    rapidxml::xml_node<>* pFaceIndex = faceRoot->first_node();
    for (; pFaceIndex; pFaceIndex = pFaceIndex->next_sibling())
    {
        const char* pzFace = pFaceIndex->value();
        int     a, b, c;
        sscanf(pzFace, "%d %d %d", &a, &b, &c);
        m_arFace.push_back(short(a));
        m_arFace.push_back(short(b));
        m_arFace.push_back(short(c));
    }


    glBindVertexArray(m_VAO);     // �� VAO		
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_arFace.size() * sizeof(short), &m_arFace.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ����������Ϣ
void ModelStd::ParseVertex(rapidxml::xml_node<>* vertRoot)
{
    std::vector<Vertex>         arVert;
    rapidxml::xml_attribute<>*  attrSize = vertRoot->first_attribute("size");
    rapidxml::xml_node<>*       vertNode = vertRoot->first_node();
    for (; vertNode; vertNode = vertNode->next_sibling())
    {
        const char* pzVert = vertNode->value();
        SkinVertex      vertex;
        sscanf(pzVert, "%f %f %f %f %f %f %f %f",
            &vertex.xyz.x,
            &vertex.xyz.y,
            &vertex.xyz.z,
            &vertex.uv.x,
            &vertex.uv.y,
            &vertex.nxyz.x,
            &vertex.nxyz.y,
            &vertex.nxyz.z);

        // ���� z y
       // float	temp = vertex.xyz.z;
       // vertex.xyz.z = vertex.xyz.y;
       // vertex.xyz.y = -temp;

        m_arVertex.push_back(vertex);
        m_arPos.push_back(vertex.xyz);
    }  

}

// ���������ź���

void ModelStd::Play(float findex)
{
    size_t	iIndex;
    if (m_arFrame.size() > 0)
    {
        iIndex = (size_t)findex % m_arFrame.size(); // ��ǰ֡ȡģ���õ�֡������
    }
    else
    {
        return;
    }
    // ��ǰ֡�ж���ͷ��
    arraybone&        arFrame    = m_arFrame[iIndex];
    arrayvertex&      arrVert    = m_arVertex;     // ��������
    arrayfloat3&      arrPos     = m_arPos;        // ������Ϣ
    arrayweight&      arrWeight  = m_arWeight;     // Ȩ���б�
    arraybone&        arrBone    = m_arBone;       // �����б�
    size_t	          iSize      = arrVert.size(); // �������

    //!	�������е�(���ڵ��weight��һһ��Ӧ��)
    for (size_t i = 0; i < iSize; ++i) // 
    {
        glm::vec3	    point(0);
        glm::vec3& pos = arrPos[i];     // ԭʼ��λ��
        SkinVertex& vtx = arrVert[i];    // ���ջ��Ƶ�����
        vtx.xyz = glm::vec3(0);
        weight_list& wgtList = arrWeight[i];  // ��ǰ����Ȩ���б�
        size_t	        iWgt = wgtList.size();
        //!	loop all weight ( )
        for (size_t j = 0; j < iWgt; ++j) // ѭ������Ȩ��
        {
            size_t	iIndex = wgtList[j].m_index;
            point = arrBone[iIndex] * glm::vec4(pos, 1.0);   // λ�ñ任

            glm::mat4 mat1 = arFrame[iIndex];
            glm::mat4 mat2 = wgtList[j].m_weight;
            glm::vec4 vec4 = glm::vec4(point, 1.0);

            glm::vec3 temp = mat1 * mat2 * vec4;  // ֡��Ϣ * Ȩ�� * λ��

            vtx.xyz += temp;
           // vtx.xyz += arFrame[iIndex] * wgtList[j].m_weight * glm::vec4(point, 1.0);  // ֡��Ϣ * Ȩ�� * λ��
        }
    }

    // ��VBO����
    glBindVertexArray(m_VAO);     // �� VAO
    // �� VBO ���������
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_arVertex.size() * sizeof(Vertex), &m_arVertex.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(m_Shader.m_Uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
    glVertexAttribPointer(m_Shader.m_Normal, 3, GL_FLOAT, false, sizeof(Vertex), (void*)20);
    glEnableVertexAttribArray(m_Shader.m_Position);
    glEnableVertexAttribArray(m_Shader.m_Uv);
    glEnableVertexAttribArray(m_Shader.m_Normal);
    //glBindVertexArray(0);

}

void ModelStd::Render(float fElapsed, ThirdCamera& camera)
{
    m_times += fElapsed * 30; // ÿ��30֡��
    Play(m_times);

    m_Shader.Begin();
    {
        glm::mat4 mv;
        // ����ģ�;���
        glm::mat4 model = glm::mat4(1.0f);          // ��ʼ��Ϊ��λ����	
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1)); // ��С0.1
        glm::mat4 view = camera.GetView();         // ���ù۲����			
        glm::mat4 projection = camera.GetProject();      // ����ͶӰ����
        mv = view * model;
        glm::mat3  matNor(1); // ���� 
        matrix4ToMatrix3(matNor, mv);


        glUniform1i(m_Shader.m_Texture, 0);
        //! ���Ƶ���
        glUniformMatrix4fv(m_Shader.m_Mv, 1, false, (const GLfloat*)&mv);
        glUniformMatrix4fv(m_Shader.m_Project, 1, false, (const GLfloat*)&projection);
        glUniformMatrix3fv(m_Shader.m_NormalMat, 1, false, (const GLfloat*)&matNor);
        glUniform3f(m_Shader.m_AmbientColor, 0.2f, 0.2f, 0.2f);
        glUniform3f(m_Shader.m_LightDirection, 0.0f, 1.0f, 0.0f);
        glUniform3f(m_Shader.m_DiffuseColor, 0.3f, 0.3f, 0.3f);

        // ÿ�λ�֮ǰ��	
        glBindVertexArray(m_VAO);     // �� VAO	
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, m_arFace.size(), GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);

    }
    m_Shader.End();

}

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

// ��ȡ�ļ�����,��Ҫ�ⲿ�ͷ��ڴ�

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

void ModelStd::SetShader(Shader_DirLight shader)
{
    m_Shader = shader;
    glGenVertexArrays(1, &m_VAO); // ��������������� VAO	
    glGenBuffers(1, &m_VBO);      // �������㻺����� VBO	       
    glGenBuffers(1, &m_EBO);      // �������㻺����� VBO	       

  // // �� VBO ���������
  // glBindBuffer(GL_ARRAY_BUFFER, m_VBO);   
  // glBufferData(GL_ARRAY_BUFFER, m_arVertex.size() * sizeof(Vertex), &m_arVertex.front(), GL_STATIC_DRAW);
  // glVertexAttribPointer(m_Shader.m_Position, 3, GL_FLOAT, false, sizeof(Vertex), 0);
  // glVertexAttribPointer(m_Shader.m_Uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*)12);
  // glVertexAttribPointer(m_Shader.m_Normal, 3, GL_FLOAT, false, sizeof(Vertex), (void*)20);
  //
  // glEnableVertexAttribArray(m_Shader.m_Position);
  // glEnableVertexAttribArray(m_Shader.m_Uv);
  // glEnableVertexAttribArray(m_Shader.m_Normal);		
  //
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_arFace.size() * sizeof(short), &m_arFace.front(), GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void ModelStd::Shutdown() const
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
