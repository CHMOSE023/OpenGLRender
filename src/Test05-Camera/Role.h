#pragma once
#include <glm/glm.hpp>
#include "../Core/Camera.h"
#include "Shader_P3_C4_T2.h"
/// <summary>
/// ��ɫ��
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
    // ���ƽ�ɫ
    void  Render(float fElapsed, Camera& camera, Shader_P3_C4_T2& shader, GLuint texture, GLuint  vertexArray, int size);

public:
	glm::vec3 m_Position; // λ��
	glm::vec3 m_Target;   // Ŀ��
	float     m_Speed;    // �ٶ�
};

