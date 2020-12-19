#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	m_lightType = LightType::DIRECTIONAL;
}

void DirectionalLight::Create()
{
	m_lightID = s_totalLights++;

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
}

void DirectionalLight::Update(float deltaTime)
{
}

void DirectionalLight::Draw()
{
	SendToShader();
}

void DirectionalLight::Destroy()
{
	s_totalLights--;
}