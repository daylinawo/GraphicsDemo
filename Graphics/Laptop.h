#ifndef LAPTOP_H
#define LAPTOP_H

#include "Object.h"
#include "Model.h"
#include "FPSCamera.h"
#include "LightManager.h"

class Laptop : public Object
{
public:
	Laptop(FPSCamera& camera, LightManager& lightManager);
	~Laptop() {};

public:

	void Create(float interactDistance);
	void Update(float deltaTime);
	void Draw();
	void Destroy();

private:
	
	void UpdateVectors();
	bool canInteract();

private:

	float m_interactDistance;

	Model m_model;

	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;

	FPSCamera* m_camera;
	LightManager* m_lightManager;

};

#endif