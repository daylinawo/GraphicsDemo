#pragma once
#include "Quad.h"
#include "BoxCollider.h"

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

	float m_up;
	float m_right;
	float m_none;

	float m_dirX;
	float m_dirY;

	Quad* m_quad;
	BoxCollider m_boxCollider;

};

