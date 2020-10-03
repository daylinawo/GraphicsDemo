#include "Background.h"
#include "Screen.h"
#include "Shapes.h"

Background::Background(float r, float g, float b)
{
	m_colour = { r, g, b };
}

void Background::Update(float deltaTime)
{
}

void Background::Draw()
{
	Shapes::DrawQuad(0, 0, Screen::Instance()->GetWidth(),
					 Screen::Instance()->GetHeight(),
					 m_colour.r, m_colour.g, m_colour.b);
}


Background::~Background()
{

}