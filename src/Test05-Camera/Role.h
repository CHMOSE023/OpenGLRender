#pragma once
#include <glm/glm.hpp>
#include "../Core/Camera.h"
#include "Shader_P3_C4_T2.h"
/// <summary>
/// 角色类
/// </summary>
class Role 
{
public:
	Role();
	~Role();
public:
	void  SetTarget(glm::vec3 target);
	void  SetPosition(glm::vec3 pos);
    void  MoveCheck(const float elasped);
    // 绘制角色
    void  Render(float fElapsed, Camera& camera, Shader_P3_C4_T2& shader, GLuint texture, GLuint  vertexArray, int size);

public:
	glm::vec3 m_Position; // 位置
	glm::vec3 m_Target;   // 目标
	float     m_Speed;    // 速度
};

