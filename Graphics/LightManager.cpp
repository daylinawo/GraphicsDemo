#include "LightManager.h"
#include "Utility.h"

LightManager::LightManager()
{
	m_directionalLight = nullptr;
}
//**********************************************************************************
// update objects
//**********************************************************************************
void LightManager::Update(float deltaTime)
{
	if(m_directionalLight)
		m_directionalLight->Update(deltaTime);

	for (auto it = m_pointLights.begin(); it != m_pointLights.end(); it++)
	{
		if ((*it).second->IsActive())
		{
			(*it).second->Update(deltaTime);
		}
	}
}
//**********************************************************************************
// draw objects in scene
//**********************************************************************************
void LightManager::Draw()
{
	if (m_directionalLight)
		m_directionalLight->Draw();

	for (auto it = m_pointLights.begin(); it != m_pointLights.end(); it++)
	{
		(*it).second->Draw();
		//if ((*it).second->IsActive())
		//{
		//}
	}
}
//**********************************************************************************
// add a new point light to the scene
//**********************************************************************************
void LightManager::AddPointLight(const std::string& lightID, float x, float y, float z, float r, float g, float b)
{
	PointLight* pointLight = new PointLight();

	pointLight->Create();
	pointLight->SetAmbient(r, g, b);
	pointLight->SetDiffuse(r, g, b);
	pointLight->SetSpecular(r, g, b);
	pointLight->SetAttenuation(1.0f, 0.07f, 0.017f);
	pointLight->SetPosition(x, y, z);

	m_pointLights.insert(std::pair<std::string, PointLight*>(lightID, pointLight));
}
//**********************************************************************************
// create a directional light
//**********************************************************************************
void LightManager::CreateDirectionalLight(float r, float g, float b)
{
	if (!m_directionalLight)
	{
		m_directionalLight = new DirectionalLight();
		m_directionalLight->Create();
		m_directionalLight->SetAmbient(r, g, b);
		m_directionalLight->SetDiffuse(r, g, b);
		m_directionalLight->SetSpecular(r, g, b);
	}
}
//**********************************************************************************
// 
//**********************************************************************************
void LightManager::ToggleLight(const std::string& lightID)
{
	auto it = m_pointLights.find(lightID);

	if (it != m_pointLights.end())
	{
		(*it).second->IsActive() = !(*it).second->IsActive();
	}
	else
	{
		Utility::Log("Could not find point light: " + lightID);
	}
}
//**********************************************************************************
// 
//**********************************************************************************
void LightManager::ToggleLight(const std::string& lightID, bool flag)
{
	auto it = m_pointLights.find(lightID);

	if (it != m_pointLights.end())
	{
		(*it).second->IsActive() = flag;
	}
	else
	{
		Utility::Log("Could not find point light: " + lightID);
	}
}
//**********************************************************************************
// destroy all point lights
//**********************************************************************************
void LightManager::DestroyPointLights()
{
	for (auto it = m_pointLights.begin(); it != m_pointLights.end(); it++)
	{
		(*it).second->Destroy();
		delete (*it).second;
	}

	m_pointLights.clear();
}
//**********************************************************************************
// destroy point light by ID
//**********************************************************************************
void LightManager::DestroyPointLights(const std::string& lightID)
{
	auto it = m_pointLights.find(lightID);

	if (it == m_pointLights.end())
	{
		Utility::Log("Could not find point light: " + lightID);
	}
	else
	{
		(*it).second->Destroy();
		delete (*it).second;
		m_pointLights.erase(it);

		Utility::Log("Successfully destroyed point light: " + lightID);
	}
}
//**********************************************************************************
// destroy directional light
//**********************************************************************************
void LightManager::DestroyDirectionalLight()
{
	if (m_directionalLight)
	{
		m_directionalLight->Destroy();
		delete m_directionalLight;
	}
}
//**********************************************************************************
// destroy all lights
//**********************************************************************************
void LightManager::DestroyAllLights()
{
	DestroyPointLights();
	DestroyDirectionalLight();
}
