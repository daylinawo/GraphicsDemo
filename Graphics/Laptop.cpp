#include "Laptop.h"
#include "Texture.h"
#include "Primitives.h"
#include "Utility.h"
#include "Input.h"
#include <glm.hpp>

Laptop::Laptop(FPSCamera& camera, LightManager& lightManager)
{
	m_tag = "Laptop";

	m_model.LoadModel("Assets/Models/Laptop.obj", "LAPTOP");

	static bool isLoaded = false;

	if (!isLoaded)
	{
		Texture::CreateTexture2D("Assets/Textures/Windows.png", "WINDOWS_OS");
		isLoaded = true;
	}

	m_model.SetTexture("WINDOWS_OS");

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forward = glm::cross(m_right, m_up);

	m_camera = &camera;
	m_lightManager = &lightManager;
	m_interactDistance = 0.0f;
}

void Laptop::Create(float interactDistance)
{
	m_interactDistance = interactDistance;
	m_model.Create();
}

void Laptop::Update(float deltaTime)
{
	static bool isKeyPressed = false;

	UpdateVectors();

	if (!m_camera || !m_lightManager)
	{
		return;
	}

	if (canInteract())
	{
		Utility::Log("Ready to interact with: " + m_tag);

		if (Input::Instance()->IsKeyPressed() && !isKeyPressed)
		{
			if(Input::Instance()->IsKeyPressed(SDL_SCANCODE_1))
			{
				m_lightManager->ToggleLight("RedLight");
			}

			if(Input::Instance()->IsKeyPressed(SDL_SCANCODE_2))
			{
				m_lightManager->ToggleLight("GreenLight");
			}
			
			if(Input::Instance()->IsKeyPressed(SDL_SCANCODE_3))
			{
				m_lightManager->ToggleLight("BlueLight");
			}
		}
	}

	//track key press so that action is only performed once per key down
	isKeyPressed = Input::Instance()->IsKeyPressed();

}

void Laptop::Draw()
{
	////create a new transformation matrix for directional vectors to avoid scaling
	//glm::mat4 directionalVectorsMatrix = glm::translate(glm::mat4(1.0f), m_transform.GetPosition());
	//directionalVectorsMatrix = glm::scale(directionalVectorsMatrix, glm::vec3(1.0f));
	//SetMatrix(directionalVectorsMatrix);

	////draw directional vectors
	//Primitives::Instance()->DrawLine3D(0.0f, 0.0f, 0.0f, m_up.x, m_up.y, m_up.z, 5.0f, 0.0f, 0.0f, 1.0f);
	//Primitives::Instance()->DrawLine3D(0.0f, 0.0f, 0.0f, m_right.x, m_right.y, m_right.z, 5.0f, 0.0f, 1.0f);
	//Primitives::Instance()->DrawLine3D(0.0f, 0.0f, 0.0f, m_forward.x, m_forward.y, m_forward.z, 5.0f);

	//draw object
	SetMatrix(m_transform.GetMatrix());

	Object::SendToShader(true, true);

	m_model.Draw();
}
//**********************************************************************************
// update the Up, Forward and Right direction vectors based on object orientation
//**********************************************************************************
void Laptop::UpdateVectors()
{
	float yaw = m_transform.GetRotation().y;
	float pitch = m_transform.GetRotation().x;

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 direction = glm::vec3(sin(glm::radians(yaw)) * cos(glm::radians(pitch)),
									-sin(glm::radians(pitch)),
									cos(glm::radians(yaw)) * cos(glm::radians(pitch)));

	m_forward = glm::normalize(direction);
	m_right = glm::normalize(glm::cross(worldUp, m_forward));
	m_up = glm::normalize(glm::cross(m_forward, m_right));
}
//**********************************************************************************
// check if player can interact with object based on distance and look direction
//**********************************************************************************
bool Laptop::canInteract()
{
	glm::vec3 cameraPos = m_camera->GetTransform().GetPosition();

	glm::vec3 cameratoLaptop = Utility::Direction(m_transform.GetPosition(), cameraPos);
	glm::vec3 laptoptoCamera = Utility::Direction(cameraPos, m_transform.GetPosition());

	float dist = Utility::Distance(cameraPos, m_transform.GetPosition());

	return (glm::dot(cameratoLaptop, m_camera->GetForward()) > 0.85f &&
			glm::dot(laptoptoCamera, m_forward) > 0.85f) &&
			dist < m_interactDistance;
}

void Laptop::Destroy()
{
	m_model.UnloadTexture("WINDOWS_OS");
	m_model.Destroy();
}