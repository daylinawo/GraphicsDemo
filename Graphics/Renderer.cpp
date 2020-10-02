#include "Renderer.h"
#include "Screen.h"
#include "Input.h"


Renderer::Renderer()
{
	m_background = new Background();
	m_square = new Square(0.0f, 0.0f, 50);
}

void Renderer::Update(float deltaTime)
{
	m_square->Update(deltaTime);
}

void Renderer::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	m_background->Draw();
	m_square->Draw();

	Screen::Instance()->SwapBuffer();
}


Renderer::~Renderer()
{
	delete m_background;
	delete m_square;	

	m_background = nullptr;
	m_square = nullptr;
}