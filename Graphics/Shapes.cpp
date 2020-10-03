#include "Shapes.h"
#include "glad.h"

void Shapes::DrawQuad(float xPos, float yPos, int width, int height, float r, float g, float b)
{
	//render quad the old way
	glBegin(GL_QUADS);

	//top left color and vertex of quad
	glColor3f(r, g, b);
	glVertex3f(-width + xPos, -height + yPos, 0.0f);

	//top right color and vertex of quad
	glColor3f(r, g, b);
	glVertex3f(width + xPos, -height + yPos, 0.0f);

	//bottom right color and vertex of quad
	glColor3f(r, g, b);
	glVertex3f(width + xPos, height + yPos, 0.0f);

	//bottom left color and vertex of quad
	glColor3f(r, g, b);
	glVertex3f(-width + xPos, height + yPos, 0.0f);

	glEnd();
}
