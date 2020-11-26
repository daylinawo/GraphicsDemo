#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#include "Camera.h"

class FPSCamera : public Camera
{

public:

	FPSCamera();
	~FPSCamera();

public:

	void Update(float deltaTime);

private:

	void HandleInput();
	void MouseLook();
	void UpdateVectors();

private:


};

#endif

