#pragma once
#include "Quad.h"

class Square
{
public:

	Square(float xPos, float yPos, int size, float r = 1.0f, float g = 0.0f, float b = 0.0f);
	~Square();

public:

	void Draw();
	void Update(float deltaTime);

private:

	float m_up;
	float m_right;
	float m_none;

	float m_dirX;
	float m_dirY;

	Quad* m_quad;

};

