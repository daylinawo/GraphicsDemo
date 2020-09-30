#include "Renderer.h"
#include "Screen.h"
#include "Input.h"
#include <iostream>

const float SPEED = 2.5f;

Renderer::Renderer()
{
	float screenWidth = static_cast<float>(Screen::Instance()->GetWidth());
	float screenHeight = static_cast<float>(Screen::Instance()->GetHeight());
	float bgWidth = 400.0f;
	float bgHeight = 300.0f;

	m_quad1 = new Quad(0.0f, 0.0f, 50.0f, 50.0f, 1.0f);
	m_quad2 = new Quad(screenWidth / 2, screenHeight / 2,
					   bgWidth, bgHeight, 0.8f, 1.0f);

	m_up = 1.0f;
	m_right = 1.0f;
	m_dirX = m_right;
	m_dirY = m_up;
}

void Renderer::Update(float deltaTime)
{
//	m_dirX = 0.0f;
//	m_dirY = 0.0f;
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
//	float newXPos = x + (m_dirX * SPEED * deltaTime);
//	float newYPos = y + (m_dirY * SPEED * deltaTime);
//
//	if ((m_dirX == m_right && !(newXPos + m_quad1->GetWidth() > 1.0f)) ||
//		(m_dirX == -m_right && !(newXPos - m_quad1->GetWidth() < -1.0f)) ||
//		(m_dirY == m_up && !(newYPos + m_quad1->GetWidth() > 1.0f)) || 
//		(m_dirY == -m_up && !(newYPos - m_quad1->GetWidth() < -1.0f)))
//	{
//		m_quad1->SetPosition(newXPos, newYPos);
//	}

	float newXPos = Input::Instance()->GetMousePositionX();
	float newYPos = Input::Instance()->GetMousePositionY();

	std::cout << newXPos << std::endl;
	std::cout << newYPos << std::endl;

	m_quad1->SetPosition(newXPos, newYPos);
}

void Renderer::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	m_quad2->Draw();
	m_quad1->Draw();

	Screen::Instance()->SwapBuffer();
}


Renderer::~Renderer()
{
	delete m_quad1;
	delete m_quad2;
}