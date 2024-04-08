#pragma once
#include "Shader.h"
class Shader_P3_C3 :public Shader
{
public:
    Shader_P3_C3()
	{
		m_MVP      = -1;
		m_Position = -1;
		m_Color    = -1;
	};

	~Shader_P3_C3()
	{
	};

	virtual bool  Initialize()
	{
       const char* vs = R"(
               #version 330
               uniform   mat4   MVP;
               layout(location = 0)  in vec3   aPos;
               layout(location = 1)  in vec3   aColor;
               out       vec4   outColor;
               void main()
               {                 
                  gl_Position = MVP*vec4(aPos,  1.0);
                  outColor    = vec4(aColor,  1.0);               
                  
               }
          )";
       
        const char* ps = R"(
                #version 330               
                in        vec4      outColor;  
                out       vec4      fragment;       
                void main()
                {                    
                    fragment          =  outColor;
                   
                }
          )";
       
        bool    res = CreateShader(vs, ps);
       
        if (res)
        {
            m_MVP      = glGetUniformLocation(m_ShaderId, "MVP");           
            m_Position = glGetAttribLocation (m_ShaderId, "aPos");
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
	Location m_Color;
	
};

