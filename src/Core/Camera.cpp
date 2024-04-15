#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
Camera::Camera()
{
	m_radius    = 400;
	m_yaw       = 0;
	m_viewSize  = glm::vec2(100, 100);
	m_matView   = glm::mat4(1);
	m_matProj   = glm::mat4(1);
	m_matWorld  = glm::mat4(1);
}

Camera::~Camera(){}

float Camera::GetRadius() const
{
	return m_radius;
}

void Camera::SetRadius(float val)
{
	m_radius = val;
}

glm::vec3 Camera::GetEye() const
{
	return m_eye;
}

void Camera::SetEye(glm::vec3 val)
{
	m_eye = val;
}

void Camera::CalcDir()
{
	
	m_dir = m_target - m_eye;      // 方向=目标位置 - 眼睛位置
	m_dir = glm::normalize(m_dir); // 规格化
}

glm::vec3 Camera::GetTarget() const
{
	return m_target;
}

void Camera::SetTarget(glm::vec3 val)
{
	m_target = val;
}

glm::vec3 Camera::GetUp() const
{
	return m_up;
}

void Camera::SetUp(glm::vec3 val)
{
	m_up = val;
}

glm::vec3 Camera::GetDir() const
{
	return m_dir;
}

glm::vec3 Camera::GetRight() const
{
	return m_right;
}

void Camera::Update() 
{
	glm::vec3 upDir   = glm::normalize(m_up);	
	m_eye             = m_target - m_dir * m_radius;	            // 眼睛位置
	m_right           = glm::normalize(glm::cross(m_dir, upDir));	// 眼睛位置左侧

	m_matView         = glm::lookAt(m_eye, m_target, m_up); 	    // 计算视图矩阵
}

void Camera::SetViewSize(const glm::vec2& viewSize)
{
	m_viewSize = viewSize;
}

void Camera::SetViewSize(float x, float y)
{
	m_viewSize = glm::vec2(x,y);
}

glm::vec2 Camera::GetViewSize()
{
	return m_viewSize;
}

void Camera::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_matProj = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetProject(const glm::mat4& proj)
{
	m_matProj = proj;
}

const glm::mat4& Camera::GetProject() const
{
	// TODO: 在此处插入 return 语句
	return m_matProj;
}

const glm::mat4& Camera::GetView() const
{
	return m_matView;
}

void Camera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	m_matProj = glm::perspective(fovy, aspect, zNear, zFar);
}

// 世界坐标转化为窗口坐标
bool Camera::Project(const glm::vec4& world, glm::vec4& screen)const
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
	screen.x = screen.x * m_viewSize.x;
	screen.y = m_viewSize.y - (screen.y * m_viewSize.y);
	return  true;

}

// 世界坐标转化为窗口坐标
glm::vec2 Camera::WordToScreen(const glm::vec3& world)const
{
	glm::vec4 worlds(world.x, world.y, world.z, 1);
	glm::vec4 screens;
	Project(worlds, screens);
	return glm::vec2(screens.x, screens.y);
}

//  窗口坐标转化为世界坐标
glm::vec3 Camera::ScreenToWorld(const glm::vec2& screen)const
{
	glm::vec4  screens(screen.x, screen.y, 0, 1);
	glm::vec4  world;
	UnProject(screens, world);	

	return glm::vec3(world.x, world.y, world.z);
}


// 屏幕坐标转换为世界坐标
glm::vec3 Camera::ScreenToWorld(double mouseX, double mouseY)const
{
	int width  = m_viewSize.x;
	int height = m_viewSize.y;	

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
bool Camera::UnProject(const glm::vec4& screen, glm::vec4& world)const
{

	return true;
}

Ray Camera::CreateRayFromScreen(int x, int y) const
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
}

void Camera::RotateView(float angle)
{
	m_dir = glm::rotateY(m_dir,angle);
}

inline void Camera::RotateViewY(float angle)
{
	m_dir        = glm::rotateY(m_dir, angle);
	m_up         = glm::rotateY(m_up, angle);;
	m_right      = normalize(glm::cross(m_dir, m_up));

	float  len   = glm::length(m_eye - m_target);
	m_eye        = m_target - m_dir * len;

	m_matView    = glm::lookAt(m_eye, m_target, m_up);
}

inline void Camera::RotateViewX(float angle)
{
	glm::mat4 mat(1);
	mat       = glm::rotate(angle, m_right);

	m_dir     = glm::vec4(m_dir,1) * mat;
	m_up      = glm::vec4(m_up, 1) * mat;
	m_right   = normalize(glm::cross(m_dir, m_up));
	float len = glm::length(m_eye - m_target);
	m_eye     = m_target - m_dir * len;

	m_matView = glm::lookAt(m_eye, m_target, m_up);
}
