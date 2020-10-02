#pragma once

#include <SDL.h>

#include "Background.h"
#include "glad.h"
#include "Square.h"
#include <string>

class Renderer
{

public:

	Renderer();
	~Renderer();

public:

	void Update(float deltaTime);
	void Draw();

private:

	Background* m_background;
	Square* m_square;
};

