#ifndef LIGHT_H
#define LIGHT_H

#include "Buffer.h"
#include "Transform.h"

#include <glm.hpp>

class Light
{
public:

	Light();

public:

	void Create();
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();

public:

	void SetDiffuse(const glm::vec3& diffuse);
	void SetAmbient(const glm::vec3& ambient);
	void SetSpecular(const glm::vec3& specular);

	void SetDiffuse(float r, float g, float b);
	void SetAmbient(float r, float g, float b);
	void SetSpecular(float r, float g, float b);

	void SetAttenuation(float attenuationConst, float attenuationLinear, float attenuationQuad);

public:

	void SendToShader();

private:

	bool m_isDirty;

	glm::vec3 m_color;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;
	GLfloat m_attenuationQuad;

	Buffer m_buffer;
	Transform m_transform;
};

#endif

