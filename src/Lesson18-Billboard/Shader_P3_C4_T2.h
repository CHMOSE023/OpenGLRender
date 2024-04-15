#pragma once
#include "Shader.h"
class Shader_P3_C4_T2 :public Shader
{
	typedef int Location;
public:
    Shader_P3_C4_T2()
	{
		m_MVP      = -1;
		m_Position = -1;
		m_Color    = -1;
		m_UV       = -1;
		m_Texture  = -1;
	};

	~Shader_P3_C4_T2()
	{
	};

	virtual bool  Initialize()
	{
       const char* vs = R"(
               #version 330
               uniform   mat4   MVP;
               layout(location = 0)  in vec3   aPos;
               layout(location = 1)  in vec4   aColor;
               layout(location = 2)  in vec2   aTexCoord;

               out       vec4   outColor;
               out       vec2   outTexCoord; 
      
               void main()
               {
                  gl_Position = MVP * vec4(aPos,  1.0);
                  outColor    = aColor;
                  outTexCoord = aTexCoord;
               }
          )";
       
        const char* ps = R"(
                #version 330
                uniform   sampler2D texture;
                in        vec4      outColor;
                in        vec2      outTexCoord;

                out       vec4      fragment;       
                void main()
                {
                    vec4 textureColor = texture2D(texture,outTexCoord);
                    //fragment          = textureColor * outColor;
                    if(textureColor.a<=0.2) // »ìºÏ
                    {
                       discard;
                    }else{
                      fragment = textureColor * outColor;
                    }                  
                }
          )";
       
        bool    res = CreateShader(vs, ps);
       
        if (res)
        {
            m_MVP      = glGetUniformLocation(m_ShaderId, "MVP");
            m_Texture  = glGetUniformLocation(m_ShaderId, "texture");
            m_Position = glGetAttribLocation (m_ShaderId, "aPos");
            m_Color    = glGetAttribLocation (m_ShaderId, "aColor");
            m_UV       = glGetAttribLocation (m_ShaderId, "aTexCoord");
        }	

        return res;
	}

    virtual void Begin()
    {
        glUseProgram(m_ShaderId);
        glEnableVertexAttribArray(m_Position);
    }
  
    virtual void  End()
    {
        glDisableVertexAttribArray(m_Position);
        glUseProgram(0);
    }

public:
	Location m_MVP;
	Location m_Position;
	Location m_Color;
	Location m_Texture;
	Location m_UV;
};

