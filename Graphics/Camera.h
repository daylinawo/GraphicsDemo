#pragma once

#include <glm.hpp>
#include "glad.h"

class Camera
{

public:

	Camera();
	~Camera();

public:

	void Update(float deltaTime);

private:

	glm::vec3 m_position;
	GLuint m_uniformIDView;
	GLuint m_uniformIDProjection;
};

