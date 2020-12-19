#include "App.h"
#include "Input.h"
#include "Pipeline.h"
#include "Primitives.h"
#include "Screen.h"
#include "Utility.h"

#include <map>
#include <glm.hpp>
#include <iostream>

App::App()
{
	m_HUD = nullptr;
	m_grid = nullptr;
	m_room = nullptr;
	m_UICam = nullptr;
	m_laptop = nullptr;
	m_skybox = nullptr;
	m_mainCam = nullptr;
	m_metalBox = nullptr;
	m_lightManager = nullptr;

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

	Primitives::Instance()->CreateObjects();

	//camera
	m_mainCam = new FPSCamera();
	m_mainCam->SetSpeed(15.0f);
	m_mainCam->SetSensitivity(0.03f);
	m_mainCam->SetPosition(0.0f, 15.0f, 35.0f);
	m_mainCam->SetRotation(-30.0f, -90.0f, 0.0f);

	m_UICam = new OrthoCamera();

	//HUD

	m_HUD = new HUD();
	m_HUD->Create();

	//grid
	m_grid = new Grid();
	m_grid->CreateGrid();
	m_grid->CreateAxes();

	//skybox
	m_skybox = new Skybox();
	m_skybox->Create();

	//room
	m_room = new Room();
	m_room->Create(30.0f, 5.0f, 40.0f);

	//lights
	m_lightManager = new LightManager();

	m_lightManager->CreateDirectionalLight(0.1f, 0.1f, 0.1f);
	m_lightManager->AddPointLight("RedLight", 20.0f, 8.0f, -10.0f, 1.0f, 0.0f, 0.0f);
	m_lightManager->AddPointLight("WhiteLight", 5.0f, 8.0f, 20.0f, 1.0f, 1.0f, 1.0f);
	m_lightManager->AddPointLight("GreenLight", -5.0f, 8.0f, -20.0f, 0.0f, 1.0f, 0.0);
	m_lightManager->AddPointLight("BlueLight", -20.0f, 8.0f, -10.0f, 0.0f, 0.0f, 1.0f);

	//crate 1
	m_crates.push_back(new Crate());
	m_crates.back()->Create();
	m_crates.back()->GetTransform().Translate(-3.0f, 4.0f, 0.0f);
	m_crates.back()->GetTransform().Rotate(5.0f, 5.0f, 5.0f);

	//crate 2
	m_crates.push_back(new Crate());
	m_crates.back()->Create();
	m_crates.back()->GetTransform().Translate(11.0f, 2.0f, -30.0f);
	m_crates.back()->GetTransform().Rotate(0.0f, 45.0f, 0.0f);
	m_crates.back()->GetTransform().Scale(1.0f, 1.0f, 1.0f);	
	
	//metalbox
	m_metalBox = new MetalBox();
	m_metalBox->Create();
	m_metalBox->GetTransform().Translate(5.0f, 1.5f, 20.0f);	
	
	//laptop
	m_laptop = new Laptop((*m_mainCam), (*m_lightManager));
	m_laptop->Create(3.0f);
	m_laptop->GetTransform().Translate(5.0f, 2.5f, 20.0f);
	m_laptop->GetTransform().Scale(3.0f, 3.0f, 3.0f);

	return true;
}
//*******************************************************************
// update graphics engine logic
//*******************************************************************
void App::Update()
{
	static bool isKeyPressed = false;

	float deltaTime = (SDL_GetTicks() - m_lastTime) * 0.001f;
	m_lastTime = SDL_GetTicks();

	Input::Instance()->Update();

	// -----------------------------------------
	// update objects
	// -----------------------------------------
	
	m_HUD->Update(deltaTime);
	m_UICam->Update(deltaTime);
	m_mainCam->Update(deltaTime);

	m_room->Update(deltaTime);
	m_laptop->Update(deltaTime);
	m_metalBox->Update(deltaTime);
	m_lightManager->Update(deltaTime);

	for (auto it = m_crates.begin(); it != m_crates.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	// -----------------------------------------
	// key press stuff
	// -----------------------------------------

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_O) && !isKeyPressed)
	{
		//toggle outline mode on/off
		(Screen::Instance()->IsOutlineMode()) ? Screen::Instance()->SetOutlineMode(false) :
												Screen::Instance()->SetOutlineMode(true);
	}

	//prevent key press state being read multiple times per second
	isKeyPressed = Input::Instance()->IsKeyPressed(SDL_SCANCODE_O);

	//use Q key to quit
	m_isRunning = !(Input::Instance()->IsKeyPressed(SDL_SCANCODE_Q));
}
//*******************************************************************
// render objects on screen
//*******************************************************************
void App::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	// -----------------------------------------
	// draw skybox
	// -----------------------------------------

	//render skybox using skybox shader
	Pipeline::Instance()->UseShader("SKYBOX_SHADER");
	Screen::Instance()->SetScreen3D();

	//disable depth testing so skybox stays in the background
	glDisable(GL_DEPTH_TEST);

	m_mainCam->Draw(true);
	m_skybox->Draw();

	glEnable(GL_DEPTH_TEST);

	// -----------------------------------------
	// draw 3D scene objects
	// -----------------------------------------

	//render all other scene objects using main shader
	Pipeline::Instance()->UseShader("MAIN_SHADER");
	Screen::Instance()->SetScreen3D();

	m_mainCam->Draw();

	m_room->Draw();
	m_laptop->Draw();
	m_metalBox->Draw();
	m_lightManager->Draw();

	//m_grid->DrawGrid();
	//m_grid->DrawAxes();

	for (auto it = m_crates.begin(); it != m_crates.end(); it++)
	{
		(*it)->Draw();
	}
	
	// -----------------------------------------
	// draw 2D scene objects
	// -----------------------------------------

	m_UICam->Draw();

	m_HUD->Draw();

	Screen::Instance()->SwapBuffer();
}
//*******************************************************************
// initialize graphics engine from configuration file
//*******************************************************************
bool App::Setup()
{
	std::map<std::string, std::string> config;

	Utility::LoadConfig("Assets/Files/Settings.ini", "BASIC", config, '=');

	Screen::Instance()->Initialize(config["WindowTitle"], 
								   std::stoi(config["ScreenWidth"]),
								   std::stoi(config["ScreenHeight"]),
								   std::stoi(config["Fullscreen"]),
								   std::stoi(config["CoreMode"]));

	Screen::Instance()->SetScreenColor(0.0f, 0.0f, 0.0f, 1.0f);

	//create main shader program
	if (!Pipeline::Instance()->CreateShaderID("Shaders/Main.vert", "Shaders/Main.frag", "MAIN_SHADER"))
	{
		return false;
	}	

	//create skybox shader program
	if (!Pipeline::Instance()->CreateShaderID("Shaders/Skybox.vert", "Shaders/Skybox.frag", "SKYBOX_SHADER"))
	{
		return false;
	}	
	
	Pipeline::Instance()->UseShader("SKYBOX_SHADER");
	Pipeline::Instance()->BindUniforms();

	Pipeline::Instance()->UseShader("MAIN_SHADER");
	Pipeline::Instance()->BindUniforms();

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
	m_room->Destroy();
	m_skybox->Destroy();
	m_laptop->Destroy();
	m_metalBox->Destroy();
	m_lightManager->DestroyAllLights();

	delete m_grid;
	delete m_room;
	delete m_skybox;
	delete m_laptop;
	delete m_metalBox;
	delete m_mainCam;
	delete m_UICam;
	delete m_lightManager;

	for (auto it = m_crates.begin(); it != m_crates.end(); it++)
	{
		(*it)->Destroy();
		delete (*it);
	}
	
	m_crates.clear();	

	Primitives::Instance()->DestroyBuffers();
	Pipeline::Instance()->DetachShaders();
	Pipeline::Instance()->DestroyShaders();
	Pipeline::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();
}

