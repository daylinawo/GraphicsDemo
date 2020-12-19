#ifndef  PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object
{
public:

	Plane(const std::string& filename = "none", const std::string& textureID = "none");
	~Plane() {}

public:

	void Create();
	void Destroy();
	void Update(float deltaTime);
	void Draw();

public:

	void SetTexture(const std::string& textureID);
	Material& GetMaterial();

private:

	Texture m_texture;
	Material m_material;
	std::string m_textureID;

};

#endif
