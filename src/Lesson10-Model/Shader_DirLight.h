#pragma once
#include "Shader.h"
class Shader_DirLight :public Shader
{
    
public:
    Shader_DirLight()
    {
      
    };

    ~Shader_DirLight()
    {
    };

    virtual bool  Initialize()
    {
        const char* vs = R"(
               #version 330
               uniform   mat4   MVP;
               layout(location = 0)  in vec3   aPos;
               layout(location = 1)  in vec3   aNormal;
               layout(location = 2)  in vec2   aTexCoord;

               uniform mat4 _mv;
               uniform mat4 _project;
               uniform mat3 _normalMat;
               uniform vec3 _ambientColor;
               
               uniform vec3 _lightDirection;
               uniform vec3 _diffuseColor;

               out       vec3   outLightWeighting;
               out       vec2   outTexCoord; 
      
               void main()
               {
                  gl_Position = _project * _mv * vec4(aPos,  1.0);
                  outTexCoord = aTexCoord;

                  vec3 tNormal      = _normalMat * aNormal;
                  float NdotL       = max(dot(tNormal, _lightDirection), 0.0);
                  //得到2者夹角的余弦指 截取到[0,1]
                  outLightWeighting = _ambientColor + _diffuseColor * NdotL;
               }
          )";

        const char* ps = R"(
                #version 330
                uniform   sampler2D _texture;
                in        vec3      outLightWeighting;
                in        vec2      outTexCoord;

                out       vec4      fragment;       
                void main()
                {
                    vec4 textureColor = texture2D(_texture, vec2(outTexCoord.s, outTexCoord.t));                   
                    fragment = vec4(outLightWeighting, textureColor.a);                             
                }
          )";

        bool    res = CreateShader(vs, ps);

        if (res)
        {
            m_Position       = glGetAttribLocation(m_ShaderId, "aPos");
            m_Uv             = glGetAttribLocation(m_ShaderId, "aTexCoord");
            m_Normal         = glGetAttribLocation(m_ShaderId, "aNormal");

            m_Mv              = glGetUniformLocation(m_ShaderId, "_mv");
            m_Project         = glGetUniformLocation(m_ShaderId, "_project");
            m_NormalMat       = glGetUniformLocation(m_ShaderId, "_normalMat");
            m_AmbientColor    = glGetUniformLocation(m_ShaderId, "_ambientColor");
            m_LightDirection  = glGetUniformLocation(m_ShaderId, "_lightDirection");
            m_DiffuseColor    = glGetUniformLocation(m_ShaderId, "_diffuseColor");
            m_Texture         = glGetUniformLocation(m_ShaderId, "_texture");
        }

        return res;
    }

    virtual void Begin()
    {
        glUseProgram(m_ShaderId);
        glEnableVertexAttribArray(m_Position);
        glEnableVertexAttribArray(m_Uv);
        glEnableVertexAttribArray(m_Normal);
    }

    virtual void  End()
    {
        glDisableVertexAttribArray(m_Position);
        glDisableVertexAttribArray(m_Uv);
        glDisableVertexAttribArray(m_Normal);
        glUseProgram(0);
    }

public:
    typedef int uniform;
    typedef int attribute;
public:
    uniform     m_Mv;
    uniform     m_Project;
    uniform     m_NormalMat;
    uniform     m_AmbientColor;
    uniform     m_LightDirection;
    uniform     m_DiffuseColor;
    uniform     m_Texture;


    attribute   m_Position;
    attribute   m_Uv;
    attribute   m_Normal;
};

