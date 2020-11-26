#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm.hpp>

class Material
{

public:

	Material();

public:

	void SetShininess(float shininess);
	void SetDiffuse(const glm::vec3& diffuse);
	void SetAmbient(const glm::vec3& ambient);
	void SetSpecular(const glm::vec3& specular);

	void SetDiffuse(float r, float g, float b);
	void SetAmbient(float r, float g, float b);
	void SetSpecular(float r, float g, float b);

public:

	void SendToShader();

private:

	float m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

#endif // !MATERIAL_H
