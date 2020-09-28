#include "Renderer.h"

const float SPEED = 0.5f;

Renderer::Renderer(SDL_Window* window)
{
	m_window = window;

	m_quad1 = new Quad(0.0f, -0.5f, 0.3f, 0.3f, 1.0f);
	m_quad2 = new Quad(0.0f, 0.0f, 0.8f, 0.8f, 0.0f, 1.0f);

	m_up = 1.0f;
	m_right = 1.0f;
	m_dirX = m_right;
	m_dirY = m_up;
}

void Renderer::Update(float deltaTime)
{
	float x = m_quad1->GetX();
	float y = m_quad1->GetY();

	float newXPos = x + (m_dirX * SPEED * deltaTime);
	float newYPos = y + (m_dirY * SPEED * deltaTime);

	if (newXPos + m_quad1->GetWidth() >= 1.0f ||
		newXPos - m_quad1->GetWidth() <= -1.0f)
	{
		m_dirX *= -1.0f;
	}
	
	if (newYPos + m_quad1->GetHeight() >= 1.0f ||
		newYPos - m_quad1->GetHeight() <= -1.0f)
	{
		m_dirY *= -1.0f;
	}

	m_quad1->SetPosition(newXPos, newYPos);
}

void Renderer::Draw()
{
	//clear the frame buffer
	glClear(GL_COLOR_BUFFER_BIT);
	m_quad2->Draw();
	m_quad1->Draw();
	SDL_GL_SwapWindow(m_window);
}


Renderer::~Renderer()
{
	delete m_quad1;
}