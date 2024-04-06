#include "Shader.h"

Shader::Shader():m_ShaderId(0)
{
}

Shader::~Shader()
{
}

bool Shader::CreateShader(const char* vertex, const char* fragment)
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
		m_ShaderId = glCreateProgram();

		if (vertexShader)
		{
			glAttachShader(m_ShaderId, vertexShader);
		}

		if (fragmentShader)
		{
			glAttachShader(m_ShaderId, fragmentShader);
		}

		glLinkProgram(m_ShaderId);

		GLint linkStatus;
		glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLchar messages[256];
			glGetProgramInfoLog(m_ShaderId, sizeof(messages), 0, messages);
			break;
		}
		glUseProgram(m_ShaderId);

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
		if (m_ShaderId)
		{
			glDeleteProgram(m_ShaderId);
			m_ShaderId = 0;
		}
	}

	return true;
}

void Shader::Begin()
{
	glUseProgram(m_ShaderId);

}

void Shader::End()
{
	glUseProgram(0);

}

