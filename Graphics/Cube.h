#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include "Buffer.h"
#include "Texture.h"
#include <gtc\matrix_transform.hpp>

class Cube : public Object
{
public:

	Cube();
	~Cube();

public:

	void Create(GLfloat width = 1.0f, GLfloat height = 1.0f, GLfloat depth = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();

private:


};


#endif