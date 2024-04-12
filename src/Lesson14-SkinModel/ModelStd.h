#pragma once
#include "rapidxml.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "ThirdCamera.h"
#include "Shader_DirLight.h"
#include <glm/gtc/type_ptr.hpp>

// ��׼ģ�ͣ�pos,uv,normal
class   ModelStd
{
private:
    struct	Weight  // �����Ȩ��ֵ
    {
    public:
        float	m_weight;
        int  	m_index;
    };
    typedef	std::vector<Weight>	        weight_list; // ����Ӱ��ȣ�һ�������ж��Ӱ��ȣ�һ����ͷ���������Ӱ��
    typedef	std::vector<weight_list>    arrayweight; // Ȩ��, ����Ӱ��ȼ���   
    typedef std::vector<glm::mat4>      arraybone;   // ��������
    typedef std::vector<arraybone>      arrayframe;  // �ؼ�֡����
    typedef std::vector<glm::vec3>      arrayfloat3; // ����
    typedef std::vector<short>          arrayface;   // ������

    struct  SkinVertex //����ṹ
    {
        glm::vec3  xyz;
        glm::vec2  uv;
        glm::vec3  nxyz;
    };
    typedef std::vector<SkinVertex>	arrayvertex;
    enum	eChunkID  // ������Ϣ
    {
        ECHUNK_MAGIC,
        ECHUNK_VERSION,
        ECHUNK_MESH_NAME,
        ECHUNK_FACE_INDEX,
        ECHUNK_FACE_MATERIAL,
        ECHUNK_FACE_DATA,
        ECHUNK_VERTEX,
        ECHUNK_LIGHTING,
        ECHUNK_LIGHT_TYPE,
        ECHUNK_LIGHT_POS,
        ECHUNK_LIGHT_DIFFUSE,
        ECHUNK_LIGHT_AMBIENT,
        ECHUNK_LIGHT_SPECALAR,
        ECHUNK_CAMERA,
        ECHUNK_CAMERA_POS,
        ECHUNK_CAMERA_VIEW,
        ECHUNK_ANIMATION_INFOR,
        ECHUNK_ANIMATION_TYPE,
        ECHUNK_ANIMATION_FILE_NAME,
        //!	skin
        ECHUNK_SKIN_BONE,
        ECHUNK_SKIN_WEIGHT_LIST,
        ECHUNK_SKIN_WEIGHT,
        ECHUNK_SKIN_ANIMATION,
        ECHUNK_SKIN_ANIMATION_NAME,
        ECHUNK_SKIN_ANIMATION_FRAME,
        //!	key frame
        ECHUNK_KEY_FRAME,
        ECHUNK_KF_NAME,
        ECHUNK_KF_DATA,
        ECHUNK_MORPH,
        ECHUNK_MORPH_NAME,
        ECHUNK_MORPH_DATA,
    };
    struct	CHUNK
    {
        CHUNK()
        {
            id = 0;
            begin = 0;
            end = 0;
            length = 0;
        }
        int	id;
        int	begin;
        int	end;
        int	length;
    };

    struct  Vertex
    {
        float   x, y, z;
        float   u, v;
        float   nx, ny, nz;
    };

public:
    ModelStd();
    ~ModelStd();
public:
    void Load(const char* meshName, const char* skinName);   
    void Render(float fElapsed, ThirdCamera& camera);
    void SetShader(Shader_DirLight shader);
private:   
    void LoadSkin(const char* fileName);                       // ����������Ϣ
    std::string	ReadString(FILE* _pFile, const CHUNK& _chunk);  
    bool LoadMesh(const char* fileName);                       // ����ģ������   
    void ParseFaceIndex(rapidxml::xml_node<>* faceRoot);       // ��������Ϣ   
    void ParseVertex(rapidxml::xml_node<>* vertRoot);          // ����������Ϣ  
    void Play(float findex);                                   // ���ź���
    char* ReadFile(const char* fileName, size_t& size);        // ��ȡ�ļ�����,��Ҫ�ⲿ�ͷ��ڴ�
    void matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src);
public:
    void Shutdown()const;
public:
    arrayfloat3     m_arPos;          // λ����Ϣ       
    arrayvertex     m_arVertex;       // ������Ϣ       
    arrayweight     m_arWeight;       // ����Ȩ����Ϣ     
    arraybone       m_arBone;         // ������Ϣ 
    arrayframe      m_arFrame;        // ����֡       
    arrayface       m_arFace;         // ��������Ϣ     
    float           m_times;          // ʱ��                                     
    unsigned        m_VAO;		      // ��������������� VAO	
    unsigned        m_VBO;		      // �������㻺����� VBO	
    unsigned        m_EBO;		      // �������㻺����� VBO	
    Shader_DirLight m_Shader;       

};

