#include "Square.h"
#include "Input.h"

#include <iostream>

const float SPEED = 32.5f;

Square::Square(float xPos, float yPos, int size, float r, float g, float b)
{
	m_quad = new Quad(xPos, yPos, size, size, r, g, b);

	m_up = 1.0f;
	m_right = 1.0f;
	m_none = 0.0f;

	m_dirX = m_right;
	m_dirY = m_up;

	m_boxCollider.SetDimension(size, size);
	m_boxCollider.SetPosition(xPos, yPos);
}

void Square::Update(float deltaTime)
{

	if (Input::Instance()->IsMouseClicked(SDL_BUTTON_LEFT))
	{
		float mouseXPos = Input::Instance()->GetMousePositionX();
		float mouseYPos = Input::Instance()->GetMousePositionY();
		
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
	float mouseXPos = Input::Instance()->GetMousePositionX();
	float mouseYPos = Input::Instance()->GetMousePositionY();

	m_quad->SetColor(0.0f, 0.0f, 0.0f);
	m_quad->SetPosition(mouseXPos, mouseYPos);
	m_boxCollider.SetPosition(mouseXPos, mouseYPos);
}

void Square::Draw()
{
	m_quad->Draw();
}

Square::~Square()
{
	delete m_quad;
	m_quad = nullptr;
}