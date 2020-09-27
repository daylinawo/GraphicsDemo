#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <string>
#include "Quad.h"

class Renderer
{
public:

public:

	Renderer(SDL_Window* window);
	~Renderer();

public:

	void Update(float deltaTime);
	void Draw();

private:

	SDL_Window* m_window;
	Quad* m_quad1;
	Quad* m_quad2;
	float m_up;
	float m_right;
	float m_dirX;
	float m_dirY;
};

