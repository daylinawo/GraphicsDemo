#ifndef APP_H
#define APP_H

#include "Cube.h"
#include "Grid.h"
#include "Quad.h"
#include "FPSCamera.h"
#include "OrthoCamera.h"
#include "Light.h"
#include "Skybox.h"

#include <vector>

class App
{
public:

	App();

public:

	bool Initialize();
	void Update();
	void Draw();
	void Exit();

public:

	bool IsRunning();

private:

	bool Setup();

private:

	int m_lastTime;
	bool m_isRunning;

	Grid* m_grid;
	Light* m_light;
	Skybox* m_skybox;

	Quad* m_floor;
	std::vector<Cube*> m_boxes;

	FPSCamera* m_3Dcamera;
	OrthoCamera* m_2DCamera;

};

#endif // !APP_H
