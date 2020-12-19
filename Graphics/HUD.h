#ifndef HUD_H
#define HUD_H

#include "Object.h"
#include "Texture.h"

class HUD : public Object
{
public:

	HUD();
	~HUD() {};

public:

	void Create();
	void Update(float deltaTime);
	void Draw();
	void Destroy();

private:

	Texture m_texture;

};

#endif

