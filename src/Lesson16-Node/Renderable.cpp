#include "Renderable.h"

Renderable::Renderable() {}

Renderable::~Renderable() {}

// ����İ�Χ����

const AABB& Renderable::GetBound()
{
	return  m_aabb;
}

void Renderable::Render(ThirdCamera& camera, const glm::mat4& model)
{
}

