#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#include "Camera.h"
#include <glm.hpp>

class FPSCamera : public Camera
{

public:

	FPSCamera();
	~FPSCamera() {};

public:

	virtual void Update(float deltaTime);
	virtual void Draw(bool isSkybox = false);

public:

	const glm::vec3& GetForward();

private:

	virtual bool HandleInput();

	void MouseLook();
	void UpdateVectors();

private:

	glm::vec3 m_worldUp;
};

#endif

