#pragma once

#include "Vector.h"

class BoxCollider
{

public:

	void SetPosition(float xPos, float yPos);
	void SetDimension(int width, int height);

public:

	bool IsColliding(const BoxCollider& secondBox) const;

private:

	void CreateBox();

private:

	Vector<float> m_position;
	Vector<float> m_dimension;
	Vector<float> m_max;
	Vector<float> m_min;

};

