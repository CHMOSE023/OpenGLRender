#pragma once
#include <glm/glm.hpp>
#include "AABB.h"
#include "ThirdCamera.h"
/// <summary>
/// ��Ⱦ����ӿ�
/// </summary>
class Renderable
{
protected:
	AABB m_aabb;
public:
	Renderable();;
	virtual~Renderable();;

	// ����İ�Χ����
	const AABB& GetBound();

	// ���ƺ���
	virtual void Render(ThirdCamera& camera, const glm::mat4& model);

};

