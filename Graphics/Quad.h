#ifndef QUAD_H
#define QUAD_H

#include "Object.h"
#include "Texture.h"

class Quad : public Object
{

public:

	Quad();

public:


	void Update(float deltaTime);
	void Draw();
	void Destroy();
	void Create(GLfloat width = 1.0f, GLfloat height = 1.0f, 
				GLfloat r = 1.0f, GLfloat g = 0.0f, GLfloat b = 0.0f);

private:


};

#endif

