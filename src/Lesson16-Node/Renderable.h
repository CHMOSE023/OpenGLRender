#pragma once
#include <glm/glm.hpp>
#include "AABB.h"
#include "ThirdCamera.h"
/// <summary>
/// 渲染对象接口
/// </summary>
class Renderable
{
protected:
	AABB m_aabb;
public:
	Renderable();;
	virtual~Renderable();;

	// 物体的包围盒子
	const AABB& GetBound();

	// 绘制函数
	virtual void Render(ThirdCamera& camera, const glm::mat4& model);

};

