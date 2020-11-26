#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#include "Camera.h"

class OrthoCamera : public Camera
{

public:

	OrthoCamera();
	~OrthoCamera();

public:

	void Update(float deltaTime);
	void HandleInput();

private:

};

#endif 
