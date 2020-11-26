#include "Object.h"
#include "Pipeline.h"

Object::Object()
{
	m_tag = "";
	m_isLit = false;
	m_isTextured = false;

	static bool isBound = false;

	if (!isBound)
	{
		//model matrix
		Pipeline::Instance()->BindUniform("model");
		//normal matrix
		Pipeline::Instance()->BindUniform("normal");

		isBound = true;
	}
}

void Object::SendToShader()
{
	glm::mat4 modelMatrix = m_transform.GetMatrix();
	glm::mat3 normalMatrix = glm::inverse(glm::mat3(modelMatrix));

	Pipeline::Instance()->SendUniformData("isLit", m_isLit);
	Pipeline::Instance()->SendUniformData("isTextured", m_isTextured);
	Pipeline::Instance()->SendUniformData("model", modelMatrix);
	Pipeline::Instance()->SendUniformData("normal", normalMatrix, true);

	if(m_isLit)
		m_material.SendToShader();
}

void Object::Rotate(float pitch, float yaw, float roll)
{
	m_transform.Rotate(pitch, yaw, roll);
}

void Object::Translate(float x, float y, float z)
{
	m_transform.Translate(x, y, z);
}

void Object::Scale(float width, float height, float depth)
{
	m_transform.Scale(width, height, depth);
}

Material& Object::GetMaterial()
{
	return m_material;
}
