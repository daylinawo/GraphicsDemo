#ifndef CRATE_H
#define CRATE_H

#include "Object.h"

class Crate : public Object
{
public:

	Crate();
	~Crate() {};

public:

	void Create();
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();

private:

	Texture m_texture;
	Material m_material;

};

#endif
