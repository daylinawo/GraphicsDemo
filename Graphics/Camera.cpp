#include "Camera.h"
#include "Input.h"
#include "Pipeline.h"
#include "Screen.h"
#include "Utility.h"

#include <gtc\matrix_transform.hpp>

Camera::Camera()
{
	m_moveSpeed = 0.0f;
	m_sensitivity = 0.0f;

	m_up = { 0.0f, 1.0f, 0.0f };
	m_right = { 1.0f, 0.0f, 0.0f };
	m_forward = { 0.0f, 0.0f, -1.0f };
	m_direction = glm::vec3(0.0f);

	m_view = glm::mat4(1.0f);
}
//*******************************************************************
// Camera up-down rotation
//*******************************************************************
void Camera::RotateX(float offsetY)
{
	float tilt = m_transform.GetRotation().x;

	//clamp up-down rotation value to prevent gimbal lock
	if (tilt - offsetY < 90.0f &&
		tilt - offsetY > -90.0f)
	{
		m_transform.Rotate(-offsetY, 0.0f, 0.0f);
	}
}
//*******************************************************************
// Camera left-right rotation
//*******************************************************************
void Camera::RotateY(float offsetX)
{
	glm::vec3 eulerAngles = m_transform.GetRotation();

	float pan  = eulerAngles.y + offsetX; 

	//constrain pan between 0-360 to prevent loss of floating point precision
	pan = glm::mod(pan, 360.0f);

	m_transform.SetRotation(eulerAngles.x, pan, eulerAngles.z);
}
//*******************************************************************
// move camera up
//*******************************************************************
void Camera::MoveUp()
{
	m_direction = m_up;
}
//*******************************************************************
// move camera down
//*******************************************************************
void Camera::MoveDown()
{
	m_direction = -m_up;
}
//*******************************************************************
// move camera left
//*******************************************************************
void Camera::MoveLeft()
{
	m_direction = m_right;
}
//*******************************************************************
// move camera right
//*******************************************************************
void Camera::MoveRight()
{
	m_direction = -m_right;
}
//*******************************************************************
// move camera forwards
//*******************************************************************
void Camera::MoveForward()
{
	m_direction = m_forward;
}
//*******************************************************************
// move camera backwards
//*******************************************************************
void Camera::MoveBackwards()
{
	m_direction = -m_forward;
}
//*******************************************************************
// returns reference to view matrix
//*******************************************************************
const glm::mat4& Camera::GetMatrix()
{
	return m_view;
}
//*******************************************************************
// returns reference to transform
//*******************************************************************
const Transform& Camera::GetTransform()
{
	return m_transform;
}
//*******************************************************************
// sets move speed
//*******************************************************************
void Camera::SetSpeed(float speed)
{
	m_moveSpeed = speed;
}
//*******************************************************************
// sets mouse sensitivity
//*******************************************************************
void Camera::SetSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}
//*******************************************************************
// sets position
//*******************************************************************
void Camera::SetPosition(float x, float y, float z)
{
	m_transform.SetPosition(x, y, z);
}
//*******************************************************************
// sets rotation
//*******************************************************************
void Camera::SetRotation(float pitch, float yaw, float roll)
{
	m_transform.SetRotation(pitch, yaw, roll);
}
