#include "Renderer.h"
#include "Screen.h"
#include "Input.h"


Renderer::Renderer()
{
	m_background = new Background();
	m_squares.push_back(new Square(200.0f, 200.0f, 50));
	m_squares.push_back(new Square(400.0f, 200.0f, 50, 0.0f, 1.0f));
	m_squares.push_back(new Square(200.0f, 700.0f, 50, 0.0f, 0.0f, 1.0f));

}

void Renderer::Update(float deltaTime)
{
	for (auto it = m_squares.begin(); it != m_squares.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

void Renderer::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	m_background->Draw();

	for (auto it = m_squares.begin(); it != m_squares.end(); it++)
	{
		(*it)->Draw();
	}

	Screen::Instance()->SwapBuffer();
}


Renderer::~Renderer()
{
	delete m_background;

	for (auto it = m_squares.begin(); it != m_squares.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;	
	}

	m_background = nullptr;
}