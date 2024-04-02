#include "ProgramId.h"

ProgramId::ProgramId():m_ProgramId(0)
{
}

ProgramId::~ProgramId()
{
}

bool ProgramId::CreateProgram(const char* vertex, const char* fragment)
{
	bool error = false;
	int  vertexShader = 0;
	int  fragmentShader = 0;

	do
	{
		if (vertex)
		{
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertex, 0);
			glCompileShader(vertexShader);

			GLint   compileStatus;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
			error = compileStatus == GL_FALSE;
			if (error)
			{
				GLchar messages[256];
				glGetShaderInfoLog(vertexShader, sizeof(messages), 0, messages);
				assert(messages && 0 != 0);
				break;
			}
		}

		if (fragment)
		{
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragment, 0);
			glCompileShader(fragmentShader);

			GLint   compileStatus;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
			error = compileStatus == GL_FALSE;

			if (error)
			{
				GLchar messages[256];
				glGetShaderInfoLog(fragmentShader, sizeof(messages), 0, messages);
				assert(messages && 0 != 0);
				break;
			}
		}
		m_ProgramId = glCreateProgram();

		if (vertexShader)
		{
			glAttachShader(m_ProgramId, vertexShader);
		}

		if (fragmentShader)
		{
			glAttachShader(m_ProgramId, fragmentShader);
		}

		glLinkProgram(m_ProgramId);

		GLint linkStatus;
		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLchar messages[256];
			glGetProgramInfoLog(m_ProgramId, sizeof(messages), 0, messages);
			break;
		}
		glUseProgram(m_ProgramId);

	} while (false);

	if (error)
	{
		if (fragmentShader)
		{
			glDeleteShader(fragmentShader);
			fragmentShader = 0;
		}
		if (vertexShader)
		{
			glDeleteShader(vertexShader);
			vertexShader = 0;
		}
		if (m_ProgramId)
		{
			glDeleteProgram(m_ProgramId);
			m_ProgramId = 0;
		}
	}

	return true;
}

void ProgramId::Begin()
{
	glUseProgram(m_ProgramId);

}

void ProgramId::End()
{
	glUseProgram(0);

}

