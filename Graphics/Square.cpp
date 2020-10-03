#include "Square.h"
#include "Input.h"
#include "Shapes.h"

#include <iostream>

const float SPEED = 32.5f;

Square::Square(float xPos, float yPos, int size, float r, float g, float b)
{
	m_width = size;
	m_height = size;
	m_colour = { r, g, b };
	m_position = { xPos, yPos };

	m_up = { 0.0f, 1.0f };
	m_right = { 1.0f, 0.0f };
	m_none = { 0.0f, 0.0f };

	m_direction = m_none;

	m_boxCollider.SetDimension(size, size);
	m_boxCollider.SetPosition(xPos, yPos);
}

void Square::Update(float deltaTime)
{
	if (Input::Instance()->IsMouseClicked(SDL_BUTTON_LEFT))
	{
		float mouseXPos = static_cast<float>(Input::Instance()->GetMousePosition().x);
		float mouseYPos = static_cast<float>(Input::Instance()->GetMousePosition().y);
		
		BoxCollider collider;
		collider.SetDimension(0, 0);
		collider.SetPosition(mouseXPos, mouseYPos);

		if (m_boxCollider.IsColliding(collider))
		{
			OnCollision();
		}
	}
}

const BoxCollider& Square::GetCollider() const
{
	return m_boxCollider;
}

void Square::OnCollision()
{
	float mouseXPos = static_cast<float>(Input::Instance()->GetMousePosition().x);
	float mouseYPos = static_cast<float>(Input::Instance()->GetMousePosition().y);

	m_colour = { 0.0f, 0.0f, 0.0f };
	m_position = { mouseXPos, mouseYPos };
	m_boxCollider.SetPosition(mouseXPos, mouseYPos);
}

void Square::Draw()
{
	Shapes::DrawQuad(m_position.x, m_position.y, m_width, 
					 m_height, m_colour.r, m_colour.g, m_colour.b);
}

Square::~Square()
{
	//
}