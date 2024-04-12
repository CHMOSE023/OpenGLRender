#include "Renderable.h"

Renderable::Renderable() {}

Renderable::~Renderable() {}

// 物体的包围盒子

const AABB& Renderable::GetBound()
{
	return  m_aabb;
}

void Renderable::Render(ThirdCamera& camera, const glm::mat4& model)
{
}

