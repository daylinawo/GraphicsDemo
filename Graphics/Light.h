#ifndef LIGHT_H
#define LIGHT_H

#include "Buffer.h"
#include "Transform.h"

#include <glm.hpp>

class Light
{
public:

	enum LightType { DIRECTIONAL = 1, POINT = 2 };

public:

	Light();
	virtual ~Light() = 0 {};

public:

	virtual void Create() = 0;
	virtual void Destroy() = 0;

public:

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

public:

	void SetDiffuse(const glm::vec3& diffuse);
	void SetAmbient(const glm::vec3& ambient);
	void SetSpecular(const glm::vec3& specular);

	void SetDiffuse(float r, float g, float b);
	void SetAmbient(float r, float g, float b);
	void SetSpecular(float r, float g, float b);

	void SetAttenuation(float attenuationConst, float attenuationLinear, float attenuationQuad);
	void SetPosition(float x, float y, float z);

public:

	bool& IsActive();

	void SendToShader();

protected:

	static GLuint s_totalLights;

protected:

	bool m_isDirty;
	bool m_isActive; 

	GLuint m_lightID;

	glm::vec3 m_color;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;
	GLfloat m_attenuationQuad;

	Transform m_transform;
	LightType m_lightType;
};

#endif

