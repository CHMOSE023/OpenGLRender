#include "ThirdCamera.h"
#include <glm/gtx/rotate_vector.hpp>

ThirdCamera::ThirdCamera()
{
	m_Radius    = 400;
	m_Yaw       = 0;
	m_ViewSize  = glm::vec2(100, 100);
	m_matView   = glm::mat4(1);
	m_matProj   = glm::mat4(1);
	m_matWorld  = glm::mat4(1);
}

ThirdCamera::~ThirdCamera(){}

float ThirdCamera::GetRadius() const
{
	return m_Radius;
}

void ThirdCamera::SetRadius(float val)
{
	m_Radius = val;
}

glm::vec3 ThirdCamera::GetEye() const
{
	return m_Eye;
}

void ThirdCamera::SetEye(glm::vec3 val)
{
	m_Eye = val;
}

void ThirdCamera::CalcDir()
{
	
	m_Dir = m_Target - m_Eye;      // 方向=目标位置 - 眼睛位置
	m_Dir = glm::normalize(m_Dir); // 规格化
}

glm::vec3 ThirdCamera::GetTarget() const
{
	return m_Target;
}

void ThirdCamera::SetTarget(glm::vec3 val)
{
	m_Target = val;
}

glm::vec3 ThirdCamera::GetUp() const
{
	return m_Up;
}

void ThirdCamera::SetUp(glm::vec3 val)
{
	m_Up = val;
}

glm::vec3 ThirdCamera::GetDir() const
{
	return m_Dir;
}

glm::vec3 ThirdCamera::GetRight() const
{
	return m_Right;
}

void ThirdCamera::Update() 
{
	glm::vec3 upDir   = glm::normalize(m_Up);	
	m_Eye     = m_Target - m_Dir * m_Radius;	// 眼睛位置
	m_Right   = glm::normalize(glm::cross(m_Dir, upDir));	// 眼睛位置左侧

	m_matView = glm::lookAt(m_Eye, m_Target, m_Up); 	// 计算视图矩阵
}

void ThirdCamera::SetViewSize(const glm::vec2& viewSize)
{
	m_ViewSize = viewSize;
}

void ThirdCamera::SetViewSize(float x, float y)
{
	m_ViewSize = glm::vec2(x,y);
}

glm::vec2 ThirdCamera::GetViewSize()
{
	return m_ViewSize;
}

void ThirdCamera::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_matProj = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void ThirdCamera::SetProject(const glm::mat4& proj)
{
	m_matProj = proj;
}

const glm::mat4& ThirdCamera::GetProject() const
{
	// TODO: 在此处插入 return 语句
	return m_matProj;
}

const glm::mat4& ThirdCamera::GetView() const
{
	return m_matView;
}

void ThirdCamera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	m_matProj = glm::perspective(fovy, aspect, zNear, zFar);
}

// 世界坐标转化为窗口坐标
bool ThirdCamera::Project(const glm::vec4& world, glm::vec4& screen)
{
	screen = (m_matProj * m_matView * m_matWorld) * world;
	if (screen.w == 0.0f)
	{
		return false;
	}
	screen.x /= screen.w;
	screen.y /= screen.w;
	screen.z /= screen.w;

	// map to range 0 - 1
	screen.x = screen.x * 0.5f + 0.5f;
	screen.y = screen.y * 0.5f + 0.5f;
	screen.z = screen.z * 0.5f + 0.5f;

	// map to viewport
	screen.x = screen.x * m_ViewSize.x;
	screen.y = m_ViewSize.y - (screen.y * m_ViewSize.y);
	return  true;

}

// 世界坐标转化为窗口坐标
glm::vec2 ThirdCamera::WordToScreen(const glm::vec3& world)
{
	glm::vec4 worlds(world.x, world.y, world.z, 1);
	glm::vec4 screens;
	Project(worlds, screens);
	return glm::vec2(screens.x, screens.y);
}

//  窗口坐标转化为世界坐标
glm::vec3 ThirdCamera::ScreenToWorld(const glm::vec2& screen)
{
	glm::vec4  screens(screen.x, screen.y, 0, 1);
	glm::vec4  world;
	UnProject(screens, world);	

	return glm::vec3(world.x, world.y, world.z);
}

//  窗口坐标转化为世界坐标
bool ThirdCamera::UnProject(const glm::vec4& screen, glm::vec4& world)
{
	glm::vec4 v;
	v.x = screen.x;
	v.y = screen.y;
	v.z = screen.z;
	v.w = 1.0;

	// map from viewport to 0 - 1
	v.x = (v.x) / m_ViewSize.x;
	v.y = (m_ViewSize.y - v.y) / m_ViewSize.y;
	//v.y = (v.y - _viewPort.Y) / _viewPort.Height;

	// map to range -1 to 1
	v.x = v.x * 2.0f - 1.0f;
	v.y = v.y * 2.0f - 1.0f;
	v.z = v.z * 2.0f - 1.0f;

	// inverse逆矩阵
	glm::mat4  inverse = glm::inverse(m_matProj * m_matView * m_matWorld);
	

	v = v * inverse;
	if (v.w == 0.0f)
	{
		return false;
	}
	world = v / v.w;
	return true;
}

Ray ThirdCamera::CreateRayFromScreen(int x, int y)
{

	glm::vec4  minWorld;
	glm::vec4  maxWorld;

	glm::vec4  screen(float(x), float(y), 0, 1);
	glm::vec4  screen1(float(x), float(y), 1, 1);

	UnProject(screen, minWorld);
	UnProject(screen1, maxWorld);

	Ray     ray;	
	ray.SetOrigin(glm::vec3(minWorld.x, minWorld.y, minWorld.z));
	glm::vec3  dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
	ray.SetDirection(glm::normalize(dir));
	return  ray;
}

void ThirdCamera::RotateView(float angle)
{
	m_Dir = glm::rotateY(m_Dir,angle);
}
