#pragma once

#include "Utility.h"

using namespace Utility;

class Background
{

public:

	Background(float r = 1.0f, float g = 1.0f, float b = 1.0f);
	~Background();

public:

	void Draw();
	void Update(float deltaTime);

private:

	Colour m_colour;

};

