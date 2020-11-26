#include "App.h"
#include "Input.h"
#include "Pipeline.h"
#include "Screen.h"
#include "Utility.h"
#include <iostream>
#include <map>
#include <glm.hpp>

App::App()
{
	m_grid = nullptr;
	m_light = nullptr;
	m_3Dcamera = nullptr;
	m_2DCamera = nullptr;
	m_floor = nullptr;
	m_skybox = nullptr;

	m_isRunning = false;
	m_lastTime = SDL_GetTicks();
}
//*******************************************************************
// create a new scene
//*******************************************************************
bool App::Initialize()
{
	if (!Setup())
	{
		return false;
	}

	m_isRunning = true;

	Screen::Instance()->SetScreen3D();

	//camera
	m_3Dcamera = new FPSCamera();
	m_3Dcamera->SetSpeed(18.0f);
	m_3Dcamera->SetSensitivity(0.03f);
	m_3Dcamera->SetPosition(0.0f, 15.0f, 20.0f);
	m_3Dcamera->SetRotation(-30.0f, -90.0f, 0.0f);

	m_2DCamera = nullptr;

	//grid
	m_grid = new Grid();
	m_grid->CreateGrid();
	m_grid->CreateAxes();

	//point light
	m_light = new Light();
	m_light->Create();
	m_light->SetAmbient(1.0f, 1.0f, 1.0f);
	m_light->SetDiffuse(1.0f, 1.0f, 1.0f);
	m_light->SetSpecular(1.0f, 1.0f, 1.0f);
	m_light->SetAttenuation(1.0f, 0.027f, 0.0028f);

	//skybox
	m_skybox = new Skybox();
	m_skybox->Create();
	m_skybox->Scale(70.0f, 70.0f, 70.0f);

	m_skybox->GetMaterial().SetAmbient(0.24725f, 0.1995f, 0.0745f);
	m_skybox->GetMaterial().SetDiffuse(0.75164f, 0.60648f, 0.22648f);
	m_skybox->GetMaterial().SetSpecular(0.628281f, 0.555802f, 0.366065f);
	m_skybox->GetMaterial().SetShininess(0.4f);

	//floor
	m_floor = new Quad();
	m_floor->Create(30.0f, 30.0f, 30.0f);
	m_floor->Translate(0.0f, 1.0f, 0.0f);
	m_floor->Rotate(90.0f, 0.0f, 0.0f);

	m_floor->GetMaterial().SetAmbient(0.25f, 0.25f, 0.25f);
	m_floor->GetMaterial().SetDiffuse(0.4f, 0.4f, 0.4f);
	m_floor->GetMaterial().SetSpecular(0.774597f, 0.774597f, 0.774597f);
	m_floor->GetMaterial().SetShininess(1.0f);

	//box
	m_boxes.push_back(new Cube());
	m_boxes.back()->Create();
	m_boxes.back()->Translate(-3.0f, 8.0f, 0.0f);	
	m_boxes.back()->Rotate(30.0f, 10.0f, 0.0f);	

	m_boxes.back()->GetMaterial().SetAmbient(0.24725f, 0.1995f, 0.0745f);
	m_boxes.back()->GetMaterial().SetDiffuse(0.75164f, 0.60648f, 0.22648f);
	m_boxes.back()->GetMaterial().SetSpecular(0.628281f, 0.555802f, 0.366065f);
	m_boxes.back()->GetMaterial().SetShininess(0.4f);

	return true;
}
//*******************************************************************
// update graphics engine logic
//*******************************************************************
void App::Update()
{
	float deltaTime = (SDL_GetTicks() - m_lastTime) / 1000.0f;
	m_lastTime = SDL_GetTicks();

	Input::Instance()->Update();

	static bool isKeyPressed = false;

	//toggle outline mode on/off
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_O) && !isKeyPressed)
	{
		(Screen::Instance()->IsOutlineMode()) ? Screen::Instance()->SetOutlineMode(false) :
												Screen::Instance()->SetOutlineMode(true);
	}

	//change field of view
	if (Input::Instance()->GetMouseWheel().y)
	{
		Screen::Instance()->SetZoom(Input::Instance()->GetMouseWheel().y);
	}

	//track key press so that action is only performed once per key down
	isKeyPressed = Input::Instance()->IsKeyPressed(SDL_SCANCODE_O);

	m_isRunning = !(Input::Instance()->IsWindowClosed());

	m_3Dcamera->Update(deltaTime);
	m_light->Update(deltaTime);
	m_skybox->Update(deltaTime);
	m_floor->Update(deltaTime);

	for (auto it = m_boxes.begin(); it != m_boxes.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

}
//*******************************************************************
// render objects on screen
//*******************************************************************
void App::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	//m_grid->DrawGrid();
	//m_grid->DrawAxes();

	//turn on depth testing so objects are rendered in the correct order
	glDisable(GL_DEPTH_TEST);
	m_skybox->Draw();
	//turn on depth testing so objects are rendered in the correct order
	glEnable(GL_DEPTH_TEST);
	m_light->Draw();
	m_floor->Draw();

	for (auto it = m_boxes.begin(); it != m_boxes.end(); it++)
	{
		(*it)->Draw();
	}


	Screen::Instance()->SwapBuffer();
}
//*******************************************************************
// initialize graphics engine from configuration file
//*******************************************************************
bool App::Setup()
{
	std::map<std::string, std::string> config;

	Utility::LoadConfig("Assets/Files/Settings.ini", "BASIC", config, '=');

	Screen::Instance()->Initialize(config["WindowTitle"], std::stoi(config["ScreenWidth"]),
								   std::stoi(config["ScreenHeight"]), std::stoi(config["Fullscreen"]),
								   std::stoi(config["CoreMode"]), std::stoi(config["OpenGLScreen"]));

	Screen::Instance()->SetScreenColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (!Pipeline::Instance()->CreateProgram())
	{
		return false;
	}

	if (!Pipeline::Instance()->CreateShaders())
	{
		return false;
	}

	if (!Pipeline::Instance()->CompileShaders("Shaders/Main.vert", Pipeline::ShaderType::VERTEX))
	{
		return false;
	}

	if (!Pipeline::Instance()->CompileShaders("Shaders/Main.frag", Pipeline::ShaderType::FRAGMENT))
	{
		return false;
	}

	Pipeline::Instance()->AttachShaders();

	if (!Pipeline::Instance()->LinkProgram())
	{
		return false;
	}

	return true;
}

bool App::IsRunning()
{
	return m_isRunning;
}
//*******************************************************************
// shutdown tasks
//*******************************************************************
void App::Exit()
{
	Pipeline::Instance()->DetachShaders();
	Pipeline::Instance()->DestroyShaders();
	Pipeline::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	delete m_3Dcamera;
	delete m_2DCamera;
	delete m_grid;
	delete m_skybox;
	delete m_floor;

	m_3Dcamera = nullptr;
	m_2DCamera = nullptr;
	m_grid = nullptr;
	m_skybox = nullptr;
	m_floor = nullptr;

	for (auto it = m_boxes.begin(); it != m_boxes.end(); it++)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_boxes.clear();
}

