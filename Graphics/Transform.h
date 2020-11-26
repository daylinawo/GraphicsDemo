#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <gtc\matrix_transform.hpp>

class Transform
{

public:

	Transform();
	~Transform();

public:

	const glm::mat4& GetMatrix();

public:

	void Translate(float x, float y, float z);
	void Translate(const glm::vec3& translation);

	void Rotate(float pitch, float yaw, float roll);
	void Rotate(const glm::vec3& eulerAngles);
	
	void Scale(float width, float height, float depth);
	void Scale(const glm::vec3& scale);

	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& position);
	
	void SetRotation(float pitch, float yaw, float roll);
	void SetRotation(const glm::vec3& eulerAngles);

	void SetScale(float width, float height, float depth);
	void SetScale(const glm::vec3& scale);

	void SetIdentity();

public:

	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();

private:

	bool m_isDirty;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_transform;

};


#endif // !TRANSFORM_H

