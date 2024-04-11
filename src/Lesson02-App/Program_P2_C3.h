#pragma once
#include "ProgramId.h"
class PROGRAM_P2_C3:public ProgramId
{
	
public:
    PROGRAM_P2_C3()
	{
		m_MVP      = -1;
		m_Position = -1;
		m_Color    = -1;
	};

	~PROGRAM_P2_C3()
	{
	};

	virtual bool  Initialize()
	{
       const char* vs = R"(
               #version 330
               uniform mat4 MVP;
               in vec2 vPos;
               in vec3 vCol;

               out vec3 color;
               void main()
               {
                  gl_Position = MVP * vec4(vPos, 0.0, 1.0);
                  color = vCol;
               }
          )";

        const char* ps = R"(
                #version 330
                in vec3 color;
                out vec4 fragment;
                void main()
                {
                     fragment = vec4(color, 1.0);
                    //fragment = vec4(1.0,1,0,0);
                }
          )";

        bool    res = CreateProgram(vs, ps);

        if (res)
        {
            m_MVP      = glGetUniformLocation(m_ProgramId, "MVP");
            m_Position = glGetAttribLocation(m_ProgramId,  "vPos");
            m_Color    = glGetAttribLocation(m_ProgramId,  "vCol");;
        }	

        return true;
	}


    virtual void Begin()
    {
        glUseProgram(m_ProgramId);
        glEnableVertexAttribArray(m_Position);
        glEnableVertexAttribArray(m_Color);
    }

    virtual void  End()
    {
        glDisableVertexAttribArray(m_Position);
        glDisableVertexAttribArray(m_Color);
        glUseProgram(0);
    }
public:
	int m_MVP;
    int m_Position;
	int m_Color;
};

