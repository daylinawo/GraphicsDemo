#include "Camera.h"
#include "Screen.h"
#include "Input.h"
#include "Pipeline.h"
#include "Utility.h"

#include <gtc\matrix_transform.hpp>

const float SPEED = 2.0f;

Camera::Camera()
{
	m_position = glm::vec3(0.0f);

	Pipeline::Instance()->BindUniform("view");
	Pipeline::Instance()->BindUniform("projection");
	m_uniformIDView = Pipeline::Instance()->GetUniformID("view");
	m_uniformIDProjection = Pipeline::Instance()->GetUniformID("projection");
}

void Camera::Update(float deltaTime)
{
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		m_position.y += SPEED * deltaTime;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_LEFT))
	{
		m_position.x -= SPEED * deltaTime;

	}	
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_DOWN))
	{
		m_position.y -= SPEED * deltaTime;

	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_RIGHT))
	{
		m_position.x += SPEED * deltaTime;
	}

	//new identity matrix
	//set camera position, target and up vector
	//pass camera's matrix data to shader
	glm::mat4 view(1.0);
	view = glm::lookAt(m_position - glm::vec3(0.0f, 0.0f, -2.0f), m_position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(m_uniformIDView, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection(1.0f);
	float ScreenWidth = Screen::Instance()->GetWidth();
	float ScreenHeight = Screen::Instance()->GetHeight();
	projection = glm::perspective(glm::radians(45.0f), ScreenWidth / ScreenHeight, 0.1f, 1000.0f);
	glUniformMatrix4fv(m_uniformIDProjection, 1, GL_FALSE, &projection[0][0]);


}

Camera::~Camera()
{
}
