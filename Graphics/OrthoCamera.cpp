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
	m_view = glm::mat4(1.0f);	
}

void OrthoCamera::Draw(bool isSkybox)
{
	Pipeline::Instance()->SendUniformData("view", m_view);
	Pipeline::Instance()->SendUniformData("cameraPosition", m_transform.GetPosition());
}

bool OrthoCamera::HandleInput()
{
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		MoveUp();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_LEFT))
	{
		MoveLeft();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_DOWN))
	{
		MoveDown();
		return true;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_RIGHT))
	{
		MoveRight();
		return true;
	}

	return false;
}