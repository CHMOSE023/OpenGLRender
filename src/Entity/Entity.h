#pragma once
#include "../Shader/Shader.h"
class Entity
{
public:
	Entity() {};
	virtual ~Entity() {}; 
	virtual void Render(const Camera& camera) = 0; // ���麯���̳������ʵ��

};