#pragma once
#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class FirstCamera
{
public:
	FirstCamera();
	~FirstCamera();
public:
	void UpdateCamera(float fElapsed, int key);
	void UpdateCamera(float fElapsed);
public:	

	glm::vec3  m_Eye{0,0,0};
	glm::vec3  m_Look{ 0,0,0 };
	glm::vec3  m_Up{ 0,0,0 };
	glm::vec3  m_Right{ 0,0,0 };
	float      m_MoveSpeed;

};