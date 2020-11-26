#ifndef OBJECT_H
#define OBJECT_H

#include "Buffer.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"

#include <glm.hpp>

class Object
{

public:

	Object();
	virtual ~Object() = 0 {};

public:

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

protected:

	void SendToShader();

public:

	void Rotate(float pitch, float yaw, float roll);
	void Translate(float x, float y, float z);
	void Scale(float width, float height, float depth);

	Material& GetMaterial();

protected:

	std::string m_tag;

	bool m_isLit;
	bool m_isTextured;

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;
	Transform m_transform;

};

#endif
