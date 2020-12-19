#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "PointLight.h"
#include "DirectionalLight.h"

#include <map>

class LightManager
{
public:

	LightManager();
	~LightManager() {};

public:

	void Update(float deltaTime);
	void Draw();

	void DestroyAllLights();
	void DestroyPointLights();
	void DestroyPointLights(const std::string& lightID);
	void DestroyDirectionalLight();

public:

	void AddPointLight(const std::string& lightID, float x, float y, float z, float r, float g, float b);
	void CreateDirectionalLight(float r, float g, float b);

public:

	void ToggleLight(const std::string& lightID);
	void ToggleLight(const std::string& lightID, bool flag);

private:

	std::map<std::string, PointLight*> m_pointLights;
	DirectionalLight* m_directionalLight;

};

#endif


