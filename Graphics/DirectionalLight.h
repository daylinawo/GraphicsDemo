#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{
public:

	DirectionalLight();
	~DirectionalLight() {};

public:

	void Create();
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();

};

#endif
