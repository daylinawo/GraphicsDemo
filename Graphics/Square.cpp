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
}

void Square::Update(float deltaTime)
{
	m_dirX = 0.0f;
	m_dirY = 0.0f;
	//
	//	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_W))
	//	{
	//		m_dirY = m_up;
	//	}
	//
	//	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_A))
	//	{
	//		m_dirX = -m_right;
	//	}
	//	
	//	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_S))
	//	{
	//		m_dirY = -m_up;
	//	}	
	//	
	//	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_D))
	//	{
	//		m_dirX = m_right;
	//	}
	//
	//	float x = m_quad1->GetX();
	//	float y = m_quad1->GetY();
	//
		//float newXPos = x + (m_dirX * SPEED * deltaTime);
		//float newYPos = y + (m_dirY * SPEED * deltaTime);
	//
	//	if ((m_dirX == m_right && !(newXPos + m_quad1->GetWidth() > 1.0f)) ||
	//		(m_dirX == -m_right && !(newXPos - m_quad1->GetWidth() < -1.0f)) ||
	//		(m_dirY == m_up && !(newYPos + m_quad1->GetWidth() > 1.0f)) || 
	//		(m_dirY == -m_up && !(newYPos - m_quad1->GetWidth() < -1.0f)))
	//	{
	//		m_quad1->SetPosition(newXPos, newYPos);
	//	}

	m_dirX = Input::Instance()->GetMouseMotionX();
	m_dirY = Input::Instance()->GetMouseMotionY();

	float x = m_quad->GetX();
	float y = m_quad->GetY();

	float newXPos = x + (m_dirX * SPEED * deltaTime);
	float newYPos = y + (m_dirY * SPEED * deltaTime);

	std::cout << "Mouse motion X: " << newXPos << std::endl;
	std::cout << "Mouse motion Y: " << newYPos << std::endl;

	m_quad->SetPosition(newXPos, newYPos);
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