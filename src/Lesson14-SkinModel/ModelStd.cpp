#include "ModelStd.h"

ModelStd::ModelStd()
{
    m_times = 0;
}

ModelStd::~ModelStd()
{
    Shutdown();  //清理数据   
}

void ModelStd::Load(const char* meshName, const char* skinName)
{
    LoadMesh(meshName); // xml
    LoadSkin(skinName); // 二进制
}

// 解析骨骼信息
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
        case ECHUNK_SKIN_BONE:       // 骨头，每个骨头一个矩阵
        {
            int	iSize = chunk.length / sizeof(glm::mat4(1));
            m_arBone.resize(iSize);
            fread(&m_arBone[0], chunk.length, 1, pFile);
        }
        break;
        case ECHUNK_SKIN_WEIGHT_LIST:// 权重信息，
        {

            m_arWeight.resize(m_arVertex.size());
            int	iIndex = 0;
          
            // 
            while (ftell(pFile) < (long)chunk.end)
            {                
                //!	读weight
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
        case ECHUNK_SKIN_ANIMATION:  // 动画信息，每帧一个矩阵
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

// 加载面数据
bool ModelStd::LoadMesh(const char* fileName)
{
    /// 读文件
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

        // 解析面索引
        faceRoot = meshNode->first_node("faceIndex");
        ParseFaceIndex(faceRoot);
        vertRoot = meshNode->first_node("vertex");
        // 解析顶点数据
        ParseVertex(vertRoot);

        delete[] xmlData;
        return  true;
    }
    catch (...)
    {
        return  false;
    }   
}

// 解析面信息 
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


    glBindVertexArray(m_VAO);     // 绑定 VAO		
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_arFace.size() * sizeof(short), &m_arFace.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// 解析顶点信息
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

        // 交换 z y
       // float	temp = vertex.xyz.z;
       // vertex.xyz.z = vertex.xyz.y;
       // vertex.xyz.y = -temp;

        m_arVertex.push_back(vertex);
        m_arPos.push_back(vertex.xyz);
    }  

}

// ！！！播放函数

void ModelStd::Play(float findex)
{
    size_t	iIndex;
    if (m_arFrame.size() > 0)
    {
        iIndex = (size_t)findex % m_arFrame.size(); // 当前帧取模，得到帧数索引
    }
    else
    {
        return;
    }
    // 当前帧有多块骨头。
    arraybone&        arFrame    = m_arFrame[iIndex];
    arrayvertex&      arrVert    = m_arVertex;     // 顶点数据
    arrayfloat3&      arrPos     = m_arPos;        // 顶点信息
    arrayweight&      arrWeight  = m_arWeight;     // 权重列表
    arraybone&        arrBone    = m_arBone;       // 骨骼列表
    size_t	          iSize      = arrVert.size(); // 顶点个数

    //!	更新所有点(现在点和weight是一一对应的)
    for (size_t i = 0; i < iSize; ++i) // 
    {
        glm::vec3	    point(0);
        glm::vec3& pos = arrPos[i];     // 原始点位置
        SkinVertex& vtx = arrVert[i];    // 最终绘制点引用
        vtx.xyz = glm::vec3(0);
        weight_list& wgtList = arrWeight[i];  // 当前顶点权重列表
        size_t	        iWgt = wgtList.size();
        //!	loop all weight ( )
        for (size_t j = 0; j < iWgt; ++j) // 循环所有权重
        {
            size_t	iIndex = wgtList[j].m_index;
            point = arrBone[iIndex] * glm::vec4(pos, 1.0);   // 位置变换

            glm::mat4 mat1 = arFrame[iIndex];
            glm::mat4 mat2 = wgtList[j].m_weight;
            glm::vec4 vec4 = glm::vec4(point, 1.0);

            glm::vec3 temp = mat1 * mat2 * vec4;  // 帧信息 * 权重 * 位置

            vtx.xyz += temp;
           // vtx.xyz += arFrame[iIndex] * wgtList[j].m_weight * glm::vec4(point, 1.0);  // 帧信息 * 权重 * 位置
        }
    }

    // 更VBO数据
    glBindVertexArray(m_VAO);     // 绑定 VAO
    // 绑定 VBO 并填充数据
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
    m_times += fElapsed * 30; // 每秒30帧，
    Play(m_times);

    m_Shader.Begin();
    {
        glm::mat4 mv;
        // 设置模型矩阵
        glm::mat4 model = glm::mat4(1.0f);          // 初始化为单位矩阵	
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1)); // 缩小0.1
        glm::mat4 view = camera.GetView();         // 设置观察矩阵			
        glm::mat4 projection = camera.GetProject();      // 设置投影矩阵
        mv = view * model;
        glm::mat3  matNor(1); // 法线 
        matrix4ToMatrix3(matNor, mv);


        glUniform1i(m_Shader.m_Texture, 0);
        //! 绘制地面
        glUniformMatrix4fv(m_Shader.m_Mv, 1, false, (const GLfloat*)&mv);
        glUniformMatrix4fv(m_Shader.m_Project, 1, false, (const GLfloat*)&projection);
        glUniformMatrix3fv(m_Shader.m_NormalMat, 1, false, (const GLfloat*)&matNor);
        glUniform3f(m_Shader.m_AmbientColor, 0.2f, 0.2f, 0.2f);
        glUniform3f(m_Shader.m_LightDirection, 0.0f, 1.0f, 0.0f);
        glUniform3f(m_Shader.m_DiffuseColor, 0.3f, 0.3f, 0.3f);

        // 每次会之前绑定	
        glBindVertexArray(m_VAO);     // 绑定 VAO	
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

// 读取文件内容,需要外部释放内存

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
    glGenVertexArrays(1, &m_VAO); // 创建顶点数组对象 VAO	
    glGenBuffers(1, &m_VBO);      // 创建顶点缓冲对象 VBO	       
    glGenBuffers(1, &m_EBO);      // 创建顶点缓冲对象 VBO	       

  // // 绑定 VBO 并填充数据
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
