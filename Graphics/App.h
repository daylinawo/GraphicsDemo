#ifndef APP_H
#define APP_H

#include "Crate.h"
#include "LightManager.h"
#include "Room.h"
#include "FPSCamera.h"
#include "Grid.h"
#include "HUD.h"
#include "MetalBox.h"
#include "Laptop.h"
#include "OrthoCamera.h"
#include "Skybox.h"

#include <vector>
#include <map>

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

	HUD* m_HUD;
	FPSCamera* m_mainCam;
	OrthoCamera* m_UICam;

	Grid* m_grid;
	Room* m_room;
	Skybox* m_skybox;
	Laptop* m_laptop;
	MetalBox* m_metalBox;
	LightManager* m_lightManager;
	std::vector<Crate*> m_crates;
};

#endif
