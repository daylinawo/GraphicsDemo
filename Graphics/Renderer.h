#ifndef RENDERER_H
#define RENDERER_H

#include "Background.h"
#include "Buffer.h"
#include "Camera.h"
#include "glad.h"

#include <glm.hpp>
#include <SDL.h>

class Renderer
{

public:

	Renderer();
	~Renderer();

public:

	void Draw();
	void Update(float deltaTime);

private:

	float m_time;
	GLuint m_uniformIDModel;

	glm::vec3 m_scale;
	glm::vec3 m_position;
	glm::vec3 m_dimensions;

	glm::mat4 m_model;
	Camera* m_camera;

	Buffer m_buffer;
};

#endif



