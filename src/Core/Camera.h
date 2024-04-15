#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
/// <summary>
/// �����
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
public:
	float      GetRadius() const;	  
	void       SetRadius(float val);    // �������ĵ����۾��ľ���
	glm::vec3  GetEye() const;          
	void       SetEye(glm::vec3 val);   // �����۾���λ��
	void       CalcDir();               // ����۲췽��
	glm::vec3  GetTarget() const;     
	void       SetTarget(glm::vec3 val); // ����Ŀ���
	glm::vec3  GetUp() const;
	void       SetUp(glm::vec3 val) ;    // �������Ϸ���
	glm::vec3  GetDir() const;
	glm::vec3  GetRight() const;
	void       Update() ;                // ÿ֡���������¹۲���� lookAt()
	void       SetViewSize(const glm::vec2& viewSize);
	void       SetViewSize(float x, float y);
	glm::vec2  GetViewSize();
	void       Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
	void       SetProject(const glm::mat4& proj);
	const      glm::mat4& GetProject() const;
	const      glm::mat4& GetView() const;
	void       Perspective(float fovy, float aspect, float zNear, float zFar);       // ͸��
	bool       Project(const glm::vec4& world, glm::vec4& screen)const;              // ��������ת��Ϊ��������
	glm::vec2  WordToScreen(const glm::vec3& world)const;                            // ��������ת��Ϊ��������
	glm::vec3  ScreenToWorld(const glm::vec2& screen)const;                          // ��������ת��Ϊ��������
	glm::vec3  ScreenToWorld(double mouseX, double mouseY)const;
	bool       UnProject(const glm::vec4& screen, glm::vec4& world)const;
	Ray        CreateRayFromScreen(int x, int y)const;
	void       RotateView(float angle);                                              // �۲췽����ĳ����������תһ���ĽǶ� 
	
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
	
	glm::vec3  m_eye;		// �۾�λ��
	glm::vec3  m_up;		// ����λ��
	glm::vec3  m_right;		// ����λ�� 
	glm::vec3  m_target;	// ���ĵ�
	float      m_radius;	// ���ĵ����۾��ľ���  (���������ֵ���Զ��)
	glm::vec3  m_dir;		// �۲��  
	glm::mat4  m_matView;	// �۲����
	glm::mat4  m_matProj;	// ͶӰ���󣨱��ڹ�����룩
	glm::mat4  m_matWorld;	// ������󣨵�λ����

	glm::vec2  m_viewSize;	// �ӿڴ�С����Ļ��������������֮��ת��ʱ���õ���

	float      m_yaw;		// ��ת�Ƕ�
};
