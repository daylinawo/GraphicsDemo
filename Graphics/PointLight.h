#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"
#include "Buffer.h"

class PointLight : public Light
{
public:

	PointLight();
	~PointLight() {};

public:

	void Create();
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();

private:

	Buffer m_buffer;

};

#endif

