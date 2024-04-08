#pragma once
#include "Shader.h"
class Shader_P2_T2_C3 :public Shader
{
public:
    Shader_P2_T2_C3()
	{
		m_MVP      = -1;
		m_Position = -1;
		m_Color    = -1;
	};

	~Shader_P2_T2_C3()
	{
	};

	virtual bool  Initialize()
	{
       const char* vs = R"(
               #version 330
               uniform   mat4   MVP;
               layout(location = 0)  in vec3   aPos;
               layout(location = 1)  in vec2   aUv;
               layout(location = 2)  in vec4   aColor;
               out       vec4   outColor;
               out       vec2   outTexCoord;
               void main()
               {                 
                  gl_Position = MVP * vec4(aPos,  1.0);
                  outColor    = aColor;  
                  outTexCoord = aUv;  

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
                    fragment          = textureColor * outColor;
                   
                }
          )";
       
        bool    res = CreateShader(vs, ps);
       
        if (res)
        {
            m_MVP      = glGetUniformLocation(m_ShaderId, "MVP");           
            m_Position = glGetAttribLocation (m_ShaderId, "aPos");
            m_UV       = glGetAttribLocation (m_ShaderId, "aUv");
            m_Color    = glGetAttribLocation (m_ShaderId, "aColor");          
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
    typedef int Location;
	Location m_MVP;
	Location m_Position;
	Location m_UV;
	Location m_Color;
	
};

