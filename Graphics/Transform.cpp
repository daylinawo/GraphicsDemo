#include "Transform.h"

Transform::Transform()
{
	m_isDirty = false;
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
	m_transform = glm::mat4(1.0f);
}

const glm::mat4& Transform::GetMatrix()
{
	if (m_isDirty)
	{
		m_transform = glm::translate(glm::mat4(1.0f), m_position);
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transform = glm::scale(m_transform, m_scale);

		m_isDirty = false;
	}

	return m_transform;
}

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

const glm::vec3& Transform::GetRotation() const
{
	return m_rotation;
}

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetIdentity()
{
	m_transform = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
	m_isDirty = true;

}

void Transform::Translate(const glm::vec3& translation)
{
	m_position += translation;
	m_isDirty = true;
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	m_rotation.x += pitch;
	m_rotation.y += yaw;
	m_rotation.z += roll;
	m_isDirty = true;
}

void Transform::Rotate(const glm::vec3& eulerAngles)
{
	m_rotation += eulerAngles;
	m_isDirty = true;
}

void Transform::Scale(float width, float height, float depth)
{
	m_scale.x += width;
	m_scale.y += height;
	m_scale.z += depth;
	m_isDirty = true;
}

void Transform::Scale(const glm::vec3& scale)
{
	m_scale += scale;
	m_isDirty = true;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	m_isDirty = true;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_isDirty = true;
}

void Transform::SetRotation(float pitch, float yaw, float roll)
{
	m_rotation.x = pitch;
	m_rotation.y = yaw;
	m_rotation.z = roll;
	m_isDirty = true;
}

void Transform::SetRotation(const glm::vec3& eulerAngles)
{
	m_rotation = eulerAngles;
	m_isDirty = true;
}

void Transform::SetScale(float width, float height, float depth)
{
	m_scale.x = width;
	m_scale.y = height;
	m_scale.z = depth;
	m_isDirty = true;
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_isDirty = true;
}


Transform::~Transform()
{
}