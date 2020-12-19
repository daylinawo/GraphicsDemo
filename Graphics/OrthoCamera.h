#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#include "Camera.h"

class OrthoCamera : public Camera
{

public:

	OrthoCamera();
	~OrthoCamera() {};

public:

	virtual void Update(float deltaTime);
	virtual void Draw(bool isSkybox = false);

private:
	
	virtual bool HandleInput();

};

#endif 
