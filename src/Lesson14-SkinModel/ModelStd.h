#pragma once
#include "rapidxml.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "ThirdCamera.h"
#include "Shader_DirLight.h"
#include <glm/gtc/type_ptr.hpp>

// 标准模型，pos,uv,normal
class   ModelStd
{
private:
    struct	Weight  // 顶点的权重值
    {
    public:
        float	m_weight;
        int  	m_index;
    };
    typedef	std::vector<Weight>	        weight_list; // 顶点影响度，一个顶点有多个影响度，一个骨头被多个顶点影响
    typedef	std::vector<weight_list>    arrayweight; // 权重, 顶点影响度集合   
    typedef std::vector<glm::mat4>      arraybone;   // 骨骼数组
    typedef std::vector<arraybone>      arrayframe;  // 关键帧数组
    typedef std::vector<glm::vec3>      arrayfloat3; // 顶点
    typedef std::vector<short>          arrayface;   // 面索引

    struct  SkinVertex //顶点结构
    {
        glm::vec3  xyz;
        glm::vec2  uv;
        glm::vec3  nxyz;
    };
    typedef std::vector<SkinVertex>	arrayvertex;
    enum	eChunkID  // 骨骼信息
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
    void LoadSkin(const char* fileName);                       // 解析骨骼信息
    std::string	ReadString(FILE* _pFile, const CHUNK& _chunk);  
    bool LoadMesh(const char* fileName);                       // 加载模型数据   
    void ParseFaceIndex(rapidxml::xml_node<>* faceRoot);       // 解析面信息   
    void ParseVertex(rapidxml::xml_node<>* vertRoot);          // 解析顶点信息  
    void Play(float findex);                                   // 播放函数
    char* ReadFile(const char* fileName, size_t& size);        // 读取文件内容,需要外部释放内存
    void matrix4ToMatrix3(glm::mat3& t, const glm::mat4& src);
public:
    void Shutdown()const;
public:
    arrayfloat3     m_arPos;          // 位置信息       
    arrayvertex     m_arVertex;       // 顶点信息       
    arrayweight     m_arWeight;       // 顶点权重信息     
    arraybone       m_arBone;         // 骨骼信息 
    arrayframe      m_arFrame;        // 数据帧       
    arrayface       m_arFace;         // 面索引信息     
    float           m_times;          // 时间                                     
    unsigned        m_VAO;		      // 创建顶点数组对象 VAO	
    unsigned        m_VBO;		      // 创建顶点缓冲对象 VBO	
    unsigned        m_EBO;		      // 创建顶点缓冲对象 VBO	
    Shader_DirLight m_Shader;       

};

