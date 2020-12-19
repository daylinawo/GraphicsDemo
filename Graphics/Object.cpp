#include "Object.h"
#include "Pipeline.h"

std::stack<glm::mat3> Object::s_normalMatrix;
std::stack<glm::mat4> Object::s_modelMatrix;

Object::Object()
{
	m_tag = "";
	m_isActive = true;
	m_isLit = false;
	m_isTextured = false;

	if (s_modelMatrix.empty())
	{
		s_modelMatrix.push(glm::mat4(1.0f));
	}
}

void Object::SetIdentity()
{
	s_modelMatrix.top() = glm::mat4(1.0f);
}

void Object::SetMatrix(const glm::mat4& matrix)
{
	s_modelMatrix.top() = matrix;
}

void Object::PushMatrix()
{
	if (!s_modelMatrix.empty())
	{
		s_modelMatrix.push(s_modelMatrix.top());
	}
}

void Object::PopMatrix()
{
	if (s_modelMatrix.size() > 1)
	{
		s_modelMatrix.pop();
	}
}

void Object::SendToShader(bool isLit, bool isTextured)
{
	s_normalMatrix.push(glm::inverse(glm::mat3(s_modelMatrix.top())));

	Pipeline::Instance()->SendUniformData("isLit", isLit);
	Pipeline::Instance()->SendUniformData("isTextured", isTextured);
	Pipeline::Instance()->SendUniformData("model", s_modelMatrix.top());
	Pipeline::Instance()->SendUniformData("normal", s_normalMatrix.top(), true);
}

void Object::Rotate(float pitch, float yaw, float roll)
{
	s_modelMatrix.top() = glm::rotate(s_modelMatrix.top(), glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
	s_modelMatrix.top() = glm::rotate(s_modelMatrix.top(), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	s_modelMatrix.top() = glm::rotate(s_modelMatrix.top(), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Object::Translate(float x, float y, float z)
{
	s_modelMatrix.top() = glm::translate(s_modelMatrix.top(), glm::vec3(x, y, z));
}

void Object::Scale(float width, float height, float depth)
{
	s_modelMatrix.top() = glm::scale(s_modelMatrix.top(), glm::vec3(width, height, depth));
}

Transform& Object::GetTransform()
{
	return m_transform;
}
