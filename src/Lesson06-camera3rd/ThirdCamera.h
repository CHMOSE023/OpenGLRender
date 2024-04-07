#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
/// <summary>
/// 第三人称相机
/// </summary>
class ThirdCamera
{
public:
	ThirdCamera();
	~ThirdCamera();
public:
	float      GetRadius() const;
	void       SetRadius(float val);
	glm::vec3  GetEye() const;
	void       SetEye(glm::vec3 val); // 设置眼睛的位置
	void       CalcDir();             //计算方向
	glm::vec3  GetTarget() const;
	void       SetTarget(glm::vec3 val);
	glm::vec3  GetUp() const;
	void       SetUp(glm::vec3 val) ;
	glm::vec3  GetDir() const;
	glm::vec3  GetRight() const;
	void       Update() ;
	void       SetViewSize(const glm::vec2& viewSize);
	void       SetViewSize(float x, float y);
	glm::vec2  GetViewSize();
	void       Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	void       SetProject(const glm::mat4& proj);
	const      glm::mat4& GetProject() const;
	const      glm::mat4& GetView() const;
	void       Perspective(float fovy, float aspect, float zNear, float zFar);  // 透视
	bool       Project(const glm::vec4& world, glm::vec4& screen);              // 世界坐标转化为窗口坐标
	glm::vec2  WordToScreen(const glm::vec3& world);                            // 世界坐标转化为窗口坐标
	glm::vec3  ScreenToWorld(const glm::vec2& screen);                          // 窗口坐标转化为世界坐标
	bool       UnProject(const glm::vec4& screen, glm::vec4& world);
	Ray        CreateRayFromScreen(int x, int y);
	void       RotateView(float angle);                                         // 观察方向绕某个方向轴旋转一定的角度 

public:	
	float      m_Radius;
	float      m_Yaw;
	glm::vec2  m_ViewSize;
	glm::vec3  m_Eye;	
	glm::vec3  m_Up;
	glm::vec3  m_Right;
	glm::vec3  m_Target;
	glm::vec3  m_Dir;
	glm::mat4  m_matView;
	glm::mat4  m_matProj;
	glm::mat4  m_matWorld;	
};
