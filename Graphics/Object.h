#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Texture.h"
#include "Transform.h"

#include <stack>
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

public:

	static void SetIdentity();
	static void SetMatrix(const glm::mat4& matrix);
	static void PushMatrix();
	static void PopMatrix();
	static void SendToShader(bool isLit, bool isTextured);

	static void Rotate(float pitch, float yaw, float roll);
	static void Translate(float x, float y, float z);
	static void Scale(float width, float height, float depth);

public:

	Transform& GetTransform();

private:

	static std::stack<glm::mat4>s_modelMatrix;
	static std::stack<glm::mat3>s_normalMatrix;

protected:

	std::string m_tag;

	bool m_isActive;
	bool m_isLit;
	bool m_isTextured;

	Transform m_transform;

};

#endif
