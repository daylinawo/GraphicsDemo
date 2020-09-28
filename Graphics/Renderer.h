#pragma once

#include "glad.h"
#include <SDL.h>
#include <string>
#include "Quad.h"

class Renderer
{

public:

	Renderer();
	~Renderer();

public:

	void Update(float deltaTime);
	void Draw();

private:

	Quad* m_quad1;
	Quad* m_quad2;
	float m_up;
	float m_right;
	float m_dirX;
	float m_dirY;
};

