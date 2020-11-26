#include "FPSCamera.h"
#include "Input.h"
#include "Pipeline.h"

#include <gtc\matrix_transform.hpp>

FPSCamera::FPSCamera()
{
	m_moveSpeed = 0.0f;
	m_sensitivity = 0.0f;
	m_transform.SetRotation(0.0f, -90.0f, 0.0f);
	m_transform.SetPosition(0.0f, 3.0f, 20.0f);
}

void FPSCamera::Update(float deltaTime)
{
	HandleInput();
	MouseLook();
	UpdateVectors();

	//move camera by a velocity
	m_transform.Translate(m_direction * m_moveSpeed * deltaTime);

	glm::vec3 newPos = m_transform.GetPosition();

	//get new view matrix based on new position and rotation values
	m_view = glm::lookAt(newPos, newPos + m_forward, m_up);

	//send view matrix to shader
	Pipeline::Instance()->SendUniformData("view", m_view);
	Pipeline::Instance()->SendUniformData("cameraPosition", m_transform.GetPosition());
}

void FPSCamera::HandleInput()
{
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		MoveForward();
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_LEFT))
	{
		MoveLeft();
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_DOWN))
	{
		MoveBackwards();
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_RIGHT))
	{
		MoveRight();
	}
	else
	{
		m_direction = glm::vec3(0.0f);
	}
}

void FPSCamera::MouseLook()
{
	//get mouse delta in x
	if (Input::Instance()->GetMouseMotion().x)
	{
		RotateY(Input::Instance()->GetMouseMotion().x * m_sensitivity);
	}

	//get mouse delta in y
	if (Input::Instance()->GetMouseMotion().y)
	{
		RotateX(Input::Instance()->GetMouseMotion().y * m_sensitivity);
	}
}

void FPSCamera::UpdateVectors()
{
	glm::vec3 eulerAngles = m_transform.GetRotation();

	//updating vectors
	glm::vec3 direction = glm::vec3(cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x)),
									sin(glm::radians(eulerAngles.x)),
									sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x)));

	m_forward = glm::normalize(direction);
	m_right = glm::normalize(glm::cross(m_worldUp, m_forward));
	m_up = glm::normalize(glm::cross(m_forward, m_right));
}

FPSCamera::~FPSCamera()
{
}