#include "ThirdCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
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
	m_Eye             = m_Target - m_Dir * m_Radius;	            // 眼睛位置
	m_Right           = glm::normalize(glm::cross(m_Dir, upDir));	// 眼睛位置左侧

	m_matView         = glm::lookAt(m_Eye, m_Target, m_Up); 	    // 计算视图矩阵
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
bool ThirdCamera::Project(const glm::vec4& world, glm::vec4& screen)const
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
glm::vec2 ThirdCamera::WordToScreen(const glm::vec3& world)const
{
	glm::vec4 worlds(world.x, world.y, world.z, 1);
	glm::vec4 screens;
	Project(worlds, screens);
	return glm::vec2(screens.x, screens.y);
}

//  窗口坐标转化为世界坐标
glm::vec3 ThirdCamera::ScreenToWorld(const glm::vec2& screen)const
{
	glm::vec4  screens(screen.x, screen.y, 0, 1);
	glm::vec4  world;
	UnProject(screens, world);	

	return glm::vec3(world.x, world.y, world.z);
}


// 屏幕坐标转换为世界坐标
glm::vec3 ThirdCamera::ScreenToWorld(double mouseX, double mouseY)const
{
	int width  = m_ViewSize.x;
	int height = m_ViewSize.y;	

	// 将屏幕坐标转换为标准化设备坐标 (NDC)
	float x = (2.0f * mouseX) / width - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / height;

	// 创建裁剪坐标
	glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);
	
	// 创建逆投影矩阵和逆视图矩阵
	glm::mat4 inverseProjectionMatrix = glm::inverse(m_matProj);
	glm::mat4 inverseViewMatrix = glm::inverse(m_matView);

	// 将裁剪坐标转换为视图坐标
	glm::vec4 eyeCoords = inverseProjectionMatrix * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f); // 方向向量

	// 将视图坐标转换为世界坐标
	glm::vec4 rayWorld = inverseViewMatrix * eyeCoords;
	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

	return rayDirection;
}



//  窗口坐标转换为世界坐标
bool ThirdCamera::UnProject(const glm::vec4& screen, glm::vec4& world)const
{
	// glm::vec4 v(0);
	// v.x = screen.x;
	// v.y = screen.y;
	// v.z = screen.z;
	// v.w = 1.0;
	// 
	// // map from viewport to 0 - 1
	// v.x = (v.x) / m_ViewSize.x;
	// v.y = (m_ViewSize.y - v.y) / m_ViewSize.y;	
	// 
	// // map to range -1 to 1
	// v.x = v.x * 2.0f - 1.0f;
	// v.y = v.y * 2.0f - 1.0f;
	// v.z = v.z * 2.0f - 1.0f;
	// 
	// glm::mat4 mvp = m_matProj * m_matView * m_matWorld;
	// 
	// glm::mat4  inverse = glm::inverse(mvp); //矩阵的逆
	// 
	// v = v * inverse;
	// 
	// if (v.w == 0.0f)
	// {
	// 	return false;
	// }
	// world = v / v.w;

	//std::cout << glm::to_string(world) << std::endl;
	return true;
}

Ray ThirdCamera::CreateRayFromScreen(int x, int y) const
{
	// 射线方向向量的世界坐标
	glm::vec3 rayDirection = ScreenToWorld(x, y);

	// 计算拾取点的位置
	glm::vec3 cameraPosition = glm::vec3(glm::inverse(m_matView)[3]);
	glm::vec3 rayOrigin = cameraPosition;
	float distanceAlongRay = -rayOrigin.z / rayDirection.z;
	glm::vec3 pickPoint = rayOrigin + distanceAlongRay * rayDirection;

	Ray     ray1;
	ray1.SetDirection(rayDirection);
	ray1.SetOrigin(pickPoint);
	return  ray1;
	//// 屏幕坐标转为世界坐标
	//glm::vec4  minWorld(0);
	//glm::vec4  maxWorld(0);
	//
	//glm::vec4  screen (float(x), float(y), 0, 1); // 最近点与屏幕交点
	//glm::vec4  screen1(float(x), float(y), 1, 1); // 最远点与屏幕交点
	//
	//UnProject(screen,  minWorld);	// 反投射计算
	//UnProject(screen1, maxWorld);	//
	//
	//Ray     ray;	
	//ray.SetOrigin(glm::vec3(minWorld.x, minWorld.y, minWorld.z));
	//
	//glm::vec3  dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
	//ray.SetDirection(glm::normalize(dir));
	//return  ray;
}

void ThirdCamera::RotateView(float angle)
{
	m_Dir = glm::rotateY(m_Dir,angle);
}
