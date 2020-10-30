#pragma once
#include <SDL.h>

#include "Background.h"
#include "glad.h"

class Renderer
{

public:

	Renderer();
	~Renderer();

public:

	void Draw();
	void Update();

private:

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_colorVBO;
	GLuint m_vertexVBO;

	float m_time;
};

