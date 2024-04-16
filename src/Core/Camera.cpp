#include "Camera.h"

Camera::Camera()
{
	m_viewSize  = glm::dvec4(0,0,256, 256);
	m_matView   = glm::dmat4(1);
	m_matProj   = glm::dmat4(1);
	m_matWorld  = glm::dmat4(1);
	m_oldLength = glm::dvec3(10);

	m_target    = glm::dvec3(0, 0, 0);
	m_eye       = glm::dvec3(0, 100, 100);
	m_right     = glm::dvec3(1, 0, 0);
	m_dir       = glm::normalize(m_target - m_eye);	
	m_up        = glm::normalize(cross(m_right, m_dir));
}

Camera::~Camera(){}

// �������
void Camera::CalcDir()
{  
	m_dir = glm::normalize(m_target - m_eye); // ���� = Ŀ��λ�� - �۾�λ��
}

void Camera::SetEye(glm::dvec3 val)
{
	m_eye = val;
}


glm::dvec3 Camera::GetEye() const
{
	return m_eye;
}

void Camera::SetTarget(glm::dvec3 val)
{
	m_target = val;
}

glm::dvec3 Camera::GetTarget() const
{
	return m_target;
}


void Camera::SetUp(glm::dvec3 val)
{
	m_up = val;
}

glm::dvec3 Camera::GetUp() const
{
	return m_up;
}


glm::dvec3 Camera::GetDir() const
{
	return m_dir;
}

void Camera::SetRight(glm::dvec3 val)
{
	m_right = val;
}

glm::dvec3 Camera::GetRight() const
{
	return m_right;
}

void Camera::SetViewSize(const glm::dvec4& viewSize)
{
	m_viewSize = viewSize;
}

void Camera::SetViewSize(double x, double y)
{
	m_viewSize = glm::dvec4(x,y,x, y);
}

glm::dvec2 Camera::GetViewSize()
{
	return m_viewSize;
}

void Camera::SetProject(const glm::dmat4& proj)
{
	m_matProj = proj;
}


const glm::dmat4& Camera::GetView() const
{
	return m_matView;
}

const glm::dmat4& Camera::GetProject() const
{
	return m_matProj;
}

void Camera::Ortho(double left, double right, double bottom, double top, double zNear, double zFar)
{
	m_matProj = glm::ortho(left, right, bottom, top, zNear, zFar);
}


void Camera::Perspective(double fovy, double aspect, double zNear, double zFar)
{
	m_matProj = glm::perspective(fovy, aspect, zNear, zFar);
}


void Camera::RotateViewX(double angle)
{
	// ��������Ҳ� ���·�ת����
	glm::dmat4 mat(1);

	mat = glm::rotate(angle, m_right);

	m_dir       = glm::dvec4(m_dir, 1) * mat;
	m_up        = glm::dvec4(m_up, 1) * mat;
	m_right     = normalize(glm::cross(m_dir, m_up));
	double len  = glm::length(m_eye - m_target);
	m_eye       = m_target - m_dir * len;
	m_matView   = glm::lookAt(m_eye, m_target, m_up);
}


void Camera::RotateViewY(double angle)
{
	glm::dmat4 mat(1);

	mat         = glm::rotate(angle, glm::dvec3(0, 1, 0));
	m_dir       = glm::vec4(m_dir, 1) * mat;
	m_up        = glm::vec4(m_up, 1) * mat;;
	m_right     = normalize(glm::cross(m_dir, m_up));
	double  len = glm::length(m_eye - m_target);
	m_eye       = m_target - m_dir * len;
	m_matView   = glm::lookAt(m_eye, m_target, m_up);
}



#include<iostream>
// ָ�����ƽ������
void Camera::ScaleCameraByPos(const glm::dvec3& pos, double persent)
{	

	glm::dvec3 dir    = glm::normalize(pos - m_eye);

	double dis        = glm::length(pos - m_eye) * persent;
	
	double disCam     = glm::length(m_target - m_eye) * persent;	


	glm::dvec3 dirCam = glm::normalize(m_target - m_eye);

	m_eye    = pos - dir * dis;

	m_target = m_eye + dirCam * disCam;

	Update();
}

void Camera::RotateViewXByCenter(double angle, glm::dvec3 pos)
{	 
	//! �����۾�������ķ���
	glm::dvec3   vDir = pos - m_eye;
	/// ������ת����۾�֮��ľ���
	double       len1 = glm::length(vDir);
	/// ��ת����۾�ֱ�ӵķ���
	         vDir = normalize(vDir);
	double   len  = 0;

	glm::dmat4 mat(1);
	mat = glm::rotate(mat, angle, m_right);

	vDir = glm::dvec4(vDir,1) * mat;

	/// �Ƶ����۾���λ��
	m_eye = pos - vDir * len1;

	m_dir = glm::dvec4(m_dir, 1) * mat;
	m_up  = glm::dvec4(m_up , 1) * mat;

	m_right = glm::normalize(glm::cross(m_dir, m_up));

	len = glm::length(m_eye - m_target);
	/// �Ƶ����۲����ĵ��λ��
	m_target = m_eye + m_dir * len;

	m_matView = glm::lookAt(m_eye, m_target, m_up);
}	 
void Camera::RotateViewYByCenter(double angle, glm::dvec3 pos)
{	 
	double        len(0);
	double        len1(0);
	glm::dmat4    mat(1);

	mat = glm::rotate(mat, angle, glm::dvec3(0, 1, 0));

	glm::dvec3   vDir = pos - m_eye;

	len1  = glm::length(vDir);
	vDir  = glm::normalize(vDir);
	vDir  = glm::dvec4(vDir,1.0) * mat;
	m_eye = pos - vDir * len1;

	m_dir     = glm::dvec4(m_dir,1.0) * mat;
	m_up      = glm::dvec4(m_up, 1.0) * mat;
	m_right   = glm::normalize(glm::cross(m_dir, m_up));
	len       = glm::length(m_eye - m_target);
	m_target  = m_eye + m_dir * len;
	m_matView = glm::lookAt(m_eye, m_target, m_up);
}	 
void Camera::RotateViewZByCenter(double angle, glm::dvec3 pos)
{
	double        len(0);
	double        len1(0);
	glm::dmat4    mat(1);

	mat = glm::rotate(mat, angle, glm::dvec3(0, 0, 1));
	
	glm::dvec3   vDir = pos - m_eye;
	
	len1       = glm::length(vDir);
	vDir       = glm::normalize(vDir);
	vDir       = glm::dvec4(vDir, 1.0) * mat;
	m_eye      = pos - vDir * len1;

	m_dir      = glm::dvec4(m_dir, 1.0) * mat;
	m_up       = glm::dvec4(m_up, 1.0) * mat;
	m_right    = glm::normalize(glm::cross(m_dir, m_up));
	len        = glm::length(m_eye - m_target);
	m_target   = m_eye + m_dir * len;
	m_matView  = glm::lookAt(m_eye, m_target, m_up);
}


// ��������
Ray Camera::CreateRayFromScreen(int mouseX, int mouseY) const
{	
	//glm::dvec3 minWorld = glm::unProject(glm::dvec3(mouseX, mouseY, 0), m_matWorld, m_matProj, m_viewSize);
	//glm::dvec3 maxWorld = glm::unProject(glm::dvec3(mouseX, mouseY, 1), m_matWorld, m_matProj, m_viewSize);
	//
	//Ray ray;	
	//ray.SetOrigin(minWorld);
	//glm::dvec3 dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
	//ray.SetDirection(normalize(dir));



	int width = m_viewSize.z;
	int height = m_viewSize.w;

	// ����Ļ����ת��Ϊ��׼���豸���� (NDC)
	float x = (2.0f * mouseX) / width - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / height;

	// �����ü�����
	glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

	// ������ͶӰ���������ͼ����
	glm::mat4 inverseProjectionMatrix = glm::inverse(m_matProj);
	glm::mat4 inverseViewMatrix = glm::inverse(m_matView);

	// ���ü�����ת��Ϊ��ͼ����
	glm::dvec4 eyeCoords = inverseProjectionMatrix * clipCoords;
	eyeCoords = glm::dvec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f); // ��������

	// ����ͼ����ת��Ϊ��������
	glm::dvec4 rayWorld = inverseViewMatrix * eyeCoords;
	glm::dvec3 rayDirection = glm::normalize(glm::dvec3(rayWorld));

	// ���߷�����������������


	// ����ʰȡ���λ��
	glm::dvec3 cameraPosition = glm::dvec3(glm::inverse(m_matView)[3]);
	glm::dvec3 rayOrigin = cameraPosition;
	double distanceAlongRay = -rayOrigin.z / rayDirection.z;
	glm::dvec3 pickPoint = rayOrigin + distanceAlongRay * rayDirection;

	Ray     ray;
	ray.SetDirection(rayDirection);
	ray.SetOrigin(pickPoint);
	return  ray;

	
}

void Camera::Update()
{
	m_matView = glm::lookAt(m_eye, m_target, m_up);         // ����ģ�;���	
}
