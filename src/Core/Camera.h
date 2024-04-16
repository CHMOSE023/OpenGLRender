#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
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
	void        CalcDir();               // ����۲췽��
	glm::dvec3  GetEye() const;          
	void        SetEye(glm::dvec3 val);   // �����۾���λ��
	glm::dvec3  GetTarget() const;     
	void        SetTarget(glm::dvec3 val); // ����Ŀ���
	glm::dvec3  GetUp() const;
	void        SetUp(glm::dvec3 val) ;    // �������Ϸ���
	glm::dvec3  GetDir() const;
	void        SetRight(glm::dvec3 val);
	glm::dvec3  GetRight() const;	
	void        SetViewSize(const glm::dvec4& viewSize);
	void        SetViewSize(double x, double y);
	glm::dvec2  GetViewSize();
	void        SetProject(const glm::dmat4& proj);
	const glm::dmat4& GetView()const;
	const glm::dmat4& GetProject()const;
	void        Ortho(double left, double right, double bottom, double top, double zNear, double zFar); // ����ͶӰ
	void        Perspective(double fovy, double aspect, double zNear, double zFar);                     // ͸��ͶӰ

	/**
	*   ����ĺ����Ĺ����ǽ�������Ĺ۲췽����ĳ����������תһ���ĽǶȸı�۲��ߵ�λ�ã�Ŀ���λ�ò��仯
	*/
	void       RotateViewX(double angle);
	void       RotateViewY(double angle);
	void       RotateViewXByCenter(double angle,glm::dvec3 pos);
	void       RotateViewYByCenter(double angle,glm::dvec3 pos);
	void       RotateViewZByCenter(double angle,glm::dvec3 pos);
	void       ScaleCameraByPos(const glm::dvec3& pos, double persent); // ָ�����ƽ������

	Ray        CreateRayFromScreen(int x, int y)const;                  // ����һ������  

	void       Update();                              

public:	
	
	glm::dvec3  m_eye;		// �۾�λ��
	glm::dvec3  m_up;		// ����λ��
	glm::dvec3  m_right;	// ����λ�� 
	glm::dvec3  m_target;	// ���ĵ�
	glm::dvec3  m_dir;		// �۲췽��  
	glm::dmat4  m_matView;	// �۲����
	glm::dmat4  m_matProj;	// ͶӰ���󣨱��ڹ�����룩
	glm::dmat4  m_matWorld;	// ������󣨵�λ����

	glm::dvec4  m_viewSize;	// �ӿڴ�С����Ļ��������������֮��ת��ʱ���õ���

	glm::dvec3  m_oldLength;	
};
