#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
class Shader
{
public:
	Shader();
	~Shader();

public:
	bool CreateShader(const char* vertex, const char* fragment);
	virtual void Begin();
	virtual void End();

public:
	int  m_ShaderId;
};

