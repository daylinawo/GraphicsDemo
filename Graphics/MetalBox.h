#ifndef METAL_BOX_H
#define METAL_BOX_H

#include "Object.h"

class MetalBox : public Object
{
public:

	MetalBox();
	~MetalBox() {};

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


