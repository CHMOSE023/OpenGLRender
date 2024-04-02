#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
class ProgramId
{
public:
	ProgramId();
	~ProgramId();

public:
	bool CreateProgram(const char* vertex, const char* fragment);
	virtual void Begin();
	virtual void End();

public:
	int  m_ProgramId;
};

