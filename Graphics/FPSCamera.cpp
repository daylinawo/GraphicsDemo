#include "FPSCamera.h"
#include "Input.h"
#include "Pipeline.h"

#include <gtc\matrix_transform.hpp>

FPSCamera::FPSCamera()
{
	m_moveSpeed = 0.0f;
	m_sensitivity = 0.0f;
	m_worldUp = { 0.0f, 1.0f, 0.0f };
	m_transform.SetRotation(0.0f, -90.0f, 0.0f);
	m_transform.SetPosition(0.0f, 3.0f, 20.0f);
}

void FPSCamera::Update(float deltaTime)
{
	if (HandleInput())
	{
		//move camera by a velocity
		m_transform.Translate(m_direction * m_moveSpeed * deltaTime);
	}

	MouseLook();
	UpdateVectors();

	//get new view matrix based on new position and rotation values
	m_view = glm::lookAt(m_transform.GetPosition(), m_transform.GetPosition() + m_forward, m_up);
}

void FPSCamera::Draw(bool isSkybox)
{
	if (isSkybox)
	{
		//drop translation but keep rotation to be able to look around skybox
		glm::mat4 viewMatrix = glm::mat3(m_view);
		Pipeline::Instance()->SendUniformData("view", viewMatrix);
	}
	else
	{
		Pipeline::Instance()->SendUniformData("view", m_view);
	}

	Pipeline::Instance()->SendUniformData("cameraPosition", m_transform.GetPosition());
}

const glm::vec3& FPSCamera::GetForward()
{
	return m_forward;
}

bool FPSCamera::HandleInput()
{
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		MoveForward();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_LEFT))
	{
		MoveLeft();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_DOWN))
	{
		MoveBackwards();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_RIGHT))
	{
		MoveRight();
		return true;
	}

	return false;
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

	//updating forward direction based on rotation
	glm::vec3 direction = glm::vec3(cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x)),
									sin(glm::radians(eulerAngles.x)),
									sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x)));

	m_forward = glm::normalize(direction);
	m_right = glm::normalize(glm::cross(m_worldUp, m_forward));
	m_up = glm::normalize(glm::cross(m_forward, m_right));
}