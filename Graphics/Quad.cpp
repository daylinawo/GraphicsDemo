#include "Quad.h"
#include "glad.h"

Quad::Quad(float xPos, float yPos, float width, 
		   float height, float r, float g, float b)
{
	m_x = xPos;
	m_y = yPos;
	m_width = width;
	m_height = height;

	m_colour.r = r;
	m_colour.g = g;
	m_colour.b = b;
}

void Quad::Update()
{

}

void Quad::Draw()
{
	//render quad the old way
	glBegin(GL_QUADS);

	//top left color and vertex of quad
	glColor3f(m_colour.r, m_colour.g, m_colour.b);
	glVertex3f(-m_width + m_x, -m_height + m_y, 0.0f);

	//top right color and vertex of quad
	glColor3f(m_colour.r, m_colour.g, m_colour.b);
	glVertex3f(m_width + m_x, -m_height + m_y, 0.0f);

	//bottom right color and vertex of quad
	glColor3f(m_colour.r, m_colour.g, m_colour.b);
	glVertex3f(m_width + m_x, m_height + m_y, 0.0f);

	//bottom left color and vertex of quad
	glColor3f(m_colour.r, m_colour.g, m_colour.b);
	glVertex3f(-m_width + m_x, m_height + m_y, 0.0f);

	glEnd();
}

void Quad::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

float Quad::GetX()
{
	return m_x;
}

float Quad::GetY()
{
	return m_y;
}

float Quad::GetWidth()
{
	return m_width;
}

float Quad::GetHeight()
{
	return m_height;
}

Quad::~Quad()
{
}

