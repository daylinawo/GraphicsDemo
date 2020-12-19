#ifndef SPRITE_H
#define SPRITE_H

#include "Buffer.h"
#include "Texture.h"

class Sprite
{
public:

	Sprite();
	~Sprite() {};

public:

	void Create(const std::string& bufferID);
	void Draw();
	void Update();
	void Destroy();

public:

	void SetBuffer(const std::string& bufferID);
	void SetTexture(const std::string& textureID);

private:

	Buffer m_buffer;
	Texture m_texture;

};

#endif

