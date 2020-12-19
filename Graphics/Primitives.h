#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Buffer.h"

class Primitives
{
public:

	static Primitives* Instance();

public:
	
	void CreateCube3D();
	void CreateQuad3D();
	void CreateLine3D();

	void CreateQuad2D();
	void CreateObjects();

	void DestroyBuffers();

public:

	void DrawCube3D(bool isLit, bool isTextured);
	void DrawQuad3D(bool isLit, bool isTextured);
	void DrawLine3D(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, 
					GLfloat lineWidth, GLfloat r = 1.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);

	void DrawQuad2D(bool isLit, bool isTextured);
private:

	Primitives() {};
	Primitives(const Primitives&);
	Primitives& operator=(const Primitives&);

private:

	Buffer m_cubeBuffer3D;
	Buffer m_quadBuffer3D;
	Buffer m_lineBuffer3D;
	Buffer m_quadBuffer2D;

};

#endif
