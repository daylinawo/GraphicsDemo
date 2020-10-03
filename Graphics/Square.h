#pragma once

#include "BoxCollider.h"
#include "Vector.h"
#include "Utility.h"

using namespace Utility;

class Square
{
public:

	Square(float xPos, float yPos, int size, float r = 1.0f, float g = 0.0f, float b = 0.0f);
	~Square();

public:

	void Draw();
	void Update(float deltaTime);

public:

	const BoxCollider& GetCollider() const;
	void OnCollision();

private:

	int m_width;
	int m_height;

	Vector<float> m_direction;
	Vector<float> m_position;

	Vector<float> m_up;
	Vector<float> m_right;
	Vector<float> m_none;

	BoxCollider m_boxCollider;
	Colour m_colour;
};

