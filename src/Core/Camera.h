#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
/// <summary>
/// 摄像机
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
public:
	float      GetRadius() const;	  
	void       SetRadius(float val);    // 设置中心点与眼睛的距离
	glm::vec3  GetEye() const;          
	void       SetEye(glm::vec3 val);   // 设置眼睛的位置
	void       CalcDir();               // 计算观察方向
	glm::vec3  GetTarget() const;     
	void       SetTarget(glm::vec3 val); // 设置目标点
	glm::vec3  GetUp() const;
	void       SetUp(glm::vec3 val) ;    // 设置向上方向
	glm::vec3  GetDir() const;
	glm::vec3  GetRight() const;
	void       Update() ;                // 每帧更新生成新观察矩阵 lookAt()
	void       SetViewSize(const glm::vec2& viewSize);
	void       SetViewSize(float x, float y);
	glm::vec2  GetViewSize();
	void       Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	void       SetProject(const glm::mat4& proj);
	const      glm::mat4& GetProject() const;
	const      glm::mat4& GetView() const;
	void       Perspective(float fovy, float aspect, float zNear, float zFar);       // 透视
	bool       Project(const glm::vec4& world, glm::vec4& screen)const;              // 世界坐标转化为窗口坐标
	glm::vec2  WordToScreen(const glm::vec3& world)const;                            // 世界坐标转化为窗口坐标
	glm::vec3  ScreenToWorld(const glm::vec2& screen)const;                          // 窗口坐标转化为世界坐标
	glm::vec3  ScreenToWorld(double mouseX, double mouseY)const;
	bool       UnProject(const glm::vec4& screen, glm::vec4& world)const;
	Ray        CreateRayFromScreen(int x, int y)const;
	void       RotateView(float angle);                                              // 观察方向绕某个方向轴旋转一定的角度 
	
	void ScaleCameraByPos(const glm::vec3& pos, float persent)
	{
		glm::vec3 dir = glm::normalize(pos - m_eye);

		float dis = glm::length(pos - m_eye) * persent;

		float disCam = glm::length(m_target - m_eye) * persent;

		glm::vec3 dirCam = glm::normalize(m_target - m_eye);

		m_eye = pos - dir * dis;
		m_target = m_eye + dirCam * disCam;

		Update();
	};
	virtual void  RotateViewY(float angle);
	virtual void  RotateViewX(float angle);

public:	
	
	glm::vec3  m_eye;		// 眼睛位置
	glm::vec3  m_up;		// 向上位置
	glm::vec3  m_right;		// 朝右位置 
	glm::vec3  m_target;	// 中心点
	float      m_radius;	// 中心点与眼睛的距离  (！！！滚轮调整远近)
	glm::vec3  m_dir;		// 观察点  
	glm::mat4  m_matView;	// 观察矩阵
	glm::mat4  m_matProj;	// 投影矩阵（便于管理加入）
	glm::mat4  m_matWorld;	// 世界矩阵（单位矩阵）

	glm::vec2  m_viewSize;	// 视口大小（屏幕坐标与世界坐标之间转换时候用到）

	float      m_yaw;		// 旋转角度
};
