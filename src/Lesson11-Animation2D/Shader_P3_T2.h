#pragma once
#include "Shader.h"
class Shader_P3_T2 :public Shader
{
	typedef int Location;
public:
    Shader_P3_T2()
	{
		m_MVP      = -1;
		m_Position = -1;		
		m_UV       = -1;
		m_Texture  = -1;
	};

	~Shader_P3_T2()
	{
	};

	virtual bool  Initialize()
	{
       const char* vs = R"(
               #version 330
               uniform   mat4   MVP;
               layout(location = 0)  in vec3   aPos;             
               layout(location = 1)  in vec2   aTexCoord;
             
               out       vec2   outTexCoord; 
      
               void main()
               {
                  gl_Position = MVP * vec4(aPos,  1.0);                
                  outTexCoord = aTexCoord;
               }
          )";
       
        const char* ps = R"(
                #version 330
                uniform   sampler2D texture;
              
                in        vec2      outTexCoord;
                out       vec4      fragment;       
                void main()
                {
                    vec4 textureColor = texture2D(texture,outTexCoord);

                   if( textureColor.a <= 0.2 )
                    {
                       discard;
                    }else{
                      fragment = textureColor ;
                    }                  
                    
                }
          )";
       
        bool    res = CreateShader(vs, ps);
       
        if (res)
        {
            m_MVP      = glGetUniformLocation(m_ShaderId, "MVP");
            m_Texture  = glGetUniformLocation(m_ShaderId, "texture");

            m_Position = glGetAttribLocation (m_ShaderId, "aPos");          
            m_UV       = glGetAttribLocation (m_ShaderId, "aTexCoord");
        }	

        return res;
	}

    virtual void Begin()
    {
        glUseProgram(m_ShaderId);
        //glEnableVertexAttribArray(m_Position);
    }
  
    virtual void  End()
    {
        //glDisableVertexAttribArray(m_Position);
        glUseProgram(0);
    }

public:
	Location m_MVP;
	Location m_Position;
	Location m_Texture;
	Location m_UV;
};

