#include "OrthoCamera.h"
#include "Input.h"
#include "Pipeline.h"
#include "Utility.h"

#include <gtc\matrix_transform.hpp>

OrthoCamera::OrthoCamera()
{
	m_moveSpeed = 35.0f;
	m_sensitivity = 0.07f;
}

void OrthoCamera::Update(float deltaTime)
{

	HandleInput();

	//move camera by a velocity
	m_transform.Translate(m_direction * m_moveSpeed * deltaTime);

	glm::vec3 newPos = m_transform.GetPosition();

	m_view = glm::lookAt(newPos, newPos + m_forward, m_up);

	Pipeline::Instance()->SendUniformData("view", m_view);

}

void OrthoCamera::HandleInput()
{

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		MoveUp();
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_LEFT))
	{
		MoveLeft();
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_DOWN))
	{
		MoveDown();
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

OrthoCamera::~OrthoCamera()
{
}