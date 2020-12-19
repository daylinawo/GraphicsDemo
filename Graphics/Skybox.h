#ifndef SKYBOX_H
#define SKYBOX_H

#include "Object.h"
#include "Material.h"
#include "Buffer.h"
#include "Texture.h"

class Skybox : public Object
{
public:

	Skybox();
	~Skybox() {};

public:

	void Create();
	void Destroy();

public:

	void Draw();
	void Update(float deltaTime);

private:

	Buffer m_buffer;
	Texture m_texture;

};

#endif 
