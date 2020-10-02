#include "Background.h"
#include "Screen.h"

Background::Background(float r, float g, float b)
{
	m_quad = new Quad(0, 0, Screen::Instance()->GetWidth(), Screen::Instance()->GetHeight(), r, g, b);

}

void Background::Update(float deltaTime)
{
}

void Background::Draw()
{
	m_quad->Draw();
}


Background::~Background()
{
	delete m_quad;
	m_quad = nullptr;
}