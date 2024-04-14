#pragma once 
#include "Shader_DirLight.h"
#include <glm/glm.hpp>
#include "ThirdCamera.h"
// ����
class Terrain
{
    struct  TerrainVertex
    {
        glm::vec3  pos;
        glm::vec2  uv;
        glm::vec3  nxyz;
    };
public:
	Terrain()
	{
        m_step  = 16;
        m_size  = 1024;
        m_scale = glm::vec2(4, 4);
	};
	~Terrain() 
	{

	};
    // ���� shader
    void SetShader(Shader_DirLight shader) 
    {
        m_shader = shader;
    }
    // ��ȡ�����ļ�����
    void LoadTerrain(const char* terrainFile, int w, int h)
    {
        FILE* pFile = fopen(terrainFile, "rb");
        if (pFile == 0)
        {
            return;
        }
        unsigned char* terrain = new unsigned char[w * h];
        fread(terrain, 1, w * h, pFile);
        fclose(pFile);

        // m_shader.Initialize();
        BuildTerrain(terrain);
        delete[]terrain;
    }

    // ��ȡ�߶�����
    int Height(unsigned char* pHeightMap, int X, int Y)
    {
        int x = X % m_size;
        int y = Y % m_size;

        if (!pHeightMap)
        {
            return 0;
        }

        return pHeightMap[x + (y * m_size)] - 200; // �߶Ƚ���200

    }

    // ��ȡ�淨��
    glm::vec3 FaceNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3)
    {
        glm::vec3 normal;
        glm::vec3 vector1 = vertex2 - vertex1;
        glm::vec3 vector2 = vertex3 - vertex1;

        //����   
        normal = glm:: cross(vector1, vector2);
        normal = normalize(normal);
        return normal;

    }

    // ���ɵ���
    void BuildTerrain(unsigned char* pHeightMap)
    {
        unsigned        arSize = m_size / m_step * m_size / m_step;
        unsigned        tileSz = m_size / m_step;
        TerrainVertex* verts = new TerrainVertex[arSize];
        for (int y = 0; y < m_size / m_step; ++y)
        {
            for (int x = 0; x < m_size / m_step; ++x)
            {
                verts[y * tileSz + x].pos = glm::vec3(x * m_scale.x, Height(pHeightMap, x, y), y * m_scale.y);
                //verts[y * tileSz + x].uv    =   float2(x/8,y/8);
                verts[y * tileSz + x].uv = glm::vec2(float(x) / float(tileSz) * 64, float(y) / float(tileSz) * 64);
            }
        }

        typedef short Face[3];

        int     faceIndex = 0;
        int     faceSize = (tileSz - 1) * (tileSz - 1) * 2;
        Face* face = new Face[faceSize];
        for (int y = 0; y < tileSz - 1; ++y)
        {
            for (int x = 0; x < tileSz - 1; ++x)
            {
                face[faceIndex + 0][0] = short(y * tileSz + x);
                face[faceIndex + 0][1] = short(y * tileSz + x + 1);
                face[faceIndex + 0][2] = short((y + 1) * tileSz + x);



                face[faceIndex + 1][0] = short((y + 1) * tileSz + x);
                face[faceIndex + 1][1] = short(y * tileSz + x + 1);
                face[faceIndex + 1][2] = short((y + 1) * tileSz + x + 1);

                //! ���㷨��
                glm::vec3  nxyz = FaceNormal(verts[face[faceIndex + 0][0]].pos, verts[face[faceIndex + 0][1]].pos, verts[face[faceIndex + 0][2]].pos);
                verts[face[faceIndex + 0][0]].nxyz = nxyz;
                verts[face[faceIndex + 0][1]].nxyz = nxyz;
                verts[face[faceIndex + 0][2]].nxyz = nxyz;

                glm::vec3  nxyz1 = FaceNormal(verts[face[faceIndex + 1][0]].pos, verts[face[faceIndex + 1][1]].pos, verts[face[faceIndex + 1][2]].pos);
                verts[face[faceIndex + 1][0]].nxyz = nxyz1;
                verts[face[faceIndex + 1][1]].nxyz = nxyz1;
                verts[face[faceIndex + 1][2]].nxyz = nxyz1;

                faceIndex += 2;
            }
        }

        glGenVertexArrays(1,&m_VAO);
        glBindVertexArray(m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertex) * arSize, verts, GL_STATIC_DRAW);

        // ��ǰ����shader
        glVertexAttribPointer(m_shader.m_Position, 3, GL_FLOAT, false, sizeof(TerrainVertex), 0);
        glVertexAttribPointer(m_shader.m_Uv,       2, GL_FLOAT, false, sizeof(TerrainVertex), (void*)12);
        glVertexAttribPointer(m_shader.m_Normal,   3, GL_FLOAT, false, sizeof(TerrainVertex), (void*)20);
        glEnableVertexAttribArray(m_shader.m_Position);
        glEnableVertexAttribArray(m_shader.m_Uv);
        glEnableVertexAttribArray(m_shader.m_Normal);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * faceSize, face, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);       

        glBindVertexArray(0);

        delete[]verts;
        delete[]face;

    }
    // ���Ƶ���
    void Render(ThirdCamera& camera, const glm::mat4& model)
    {

        glm::mat4 mv;
        // ����ģ�;���
        glm::mat4 modelMat      = model;                // node��ģ��λ��	
        glm::mat4 viewMat       = camera.GetView();     // ���ù۲����		
        glm::mat4 projectionMat = camera.GetProject();  // ����ͶӰ����

        mv = viewMat * modelMat;

        glm::mat3  matNor(1); // ���� 
        Matrix4ToMatrix3(matNor, mv);

        m_shader.Begin();
        {

            glUniform1i(m_shader.m_Texture, 0);
            //! ���Ƶ���
            glUniformMatrix4fv(m_shader.m_Mv, 1, false, (const GLfloat*)&mv);
            glUniformMatrix4fv(m_shader.m_Project, 1, false, (const GLfloat*)&projectionMat);
            glUniformMatrix3fv(m_shader.m_NormalMat, 1, false, (const GLfloat*)&matNor);
            glUniform3f(m_shader.m_AmbientColor, 0.2f, 0.2f, 0.2f);
            glUniform3f(m_shader.m_LightDirection, 0.0f, 1.0f, 0.0f);
            glUniform3f(m_shader.m_DiffuseColor, 0.3f, 0.3f, 0.3f);

            // ÿ�λ�֮ǰ��	
            glBindVertexArray(m_VAO);     // �� VAO	
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            //glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_SHORT, 0);
            int size = (m_size / m_step - 1) * (m_size / m_step - 1) * 2 * 3;
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
            glBindVertexArray(0);
        }

        m_shader.End();       
    }

    // 
    void Matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src)
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

public:
    unsigned            m_VAO;
    unsigned            m_VBO;
    unsigned            m_EBO;
    unsigned            m_step;   // ��������
    unsigned            m_size;   // ͼƬ���
    glm::vec2           m_scale;  // ÿ��λ��С
    Shader_DirLight     m_shader; // shader

};
