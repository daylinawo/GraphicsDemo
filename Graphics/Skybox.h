#ifndef SKYBOX_H
#define SKYBOX_H

#include "Object.h"
#include "Material.h"

class Skybox : public Object
{
public:

	Skybox();
	~Skybox();

public:

	void Create();
	void Destroy();

public:

	void Draw();
	void Update(float deltaTime);

private:

};

#endif 
