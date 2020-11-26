#include "Material.h"
#include "Pipeline.h"

Material::Material()
{
	m_shininess = 0.0f;
	m_ambient = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);

	static bool isBound = false;

	if (!isBound)
	{
		Pipeline::Instance()->BindUniform("material.ambient");
		Pipeline::Instance()->BindUniform("material.diffuse");
		Pipeline::Instance()->BindUniform("material.specular");
		Pipeline::Instance()->BindUniform("material.shininess");

		isBound = true;
	}
}

void Material::SetShininess(float shininess)
{
	m_shininess = shininess;
}

void Material::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}

void Material::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}

void Material::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}

//*******************************************************************
// set ambient color with floats
//*******************************************************************
void Material::SetAmbient(float r, float g, float b)
{
	m_ambient.r = r;
	m_ambient.g = g;
	m_ambient.b = b;
}

//*******************************************************************
// set diffuse color with floats
//*******************************************************************
void Material::SetDiffuse(float r, float g, float b)
{
	m_diffuse.r = r;
	m_diffuse.g = g;
	m_diffuse.b = b;
}

//*******************************************************************
// set specular color with floats
//*******************************************************************
void Material::SetSpecular(float r, float g, float b)
{
	m_specular.r = r;
	m_specular.g = g;
	m_specular.b = b;
}


void Material::SendToShader()
{
	Pipeline::Instance()->SendUniformData("material.ambient", m_ambient);
	Pipeline::Instance()->SendUniformData("material.diffuse", m_diffuse);
	Pipeline::Instance()->SendUniformData("material.specular", m_specular);
	Pipeline::Instance()->SendUniformData("material.shininess", m_shininess);
}
