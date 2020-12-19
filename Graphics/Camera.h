#pragma once

#include "glad.h"
#include "Transform.h"

#include <glm.hpp>

class Camera
{

public:

	 Camera();
	 virtual ~Camera() = 0 {};

public:

	void RotateX(float offsetY);
	void RotateY(float offsetX);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackwards();

public:
	
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(bool isSkybox = false) = 0;

public:

	const glm::mat4& GetMatrix();
	const Transform& GetTransform();

	void SetSpeed(float speed);
	void SetSensitivity(float sensitivity);
	void SetPosition(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);

protected:

	virtual bool HandleInput() = 0;

protected:

	float m_moveSpeed;
	float m_sensitivity;

	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;
	glm::vec3 m_direction;

	glm::mat4 m_view;
	Transform m_transform;

};

