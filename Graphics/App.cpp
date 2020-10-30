#include "App.h"
#include "Utility.h"

#include <iostream>
#include <map>

App::App()
{
	m_isRunning = false;
	m_lastTime = SDL_GetTicks();
}

bool App::Initialize()
{
	std::map<std::string, std::string> config;

	Utility::LoadConfig("Assets/Files/Settings.ini", "BASIC", config, '=');

	Screen::Instance()->Initialize(config["WindowTitle"], std::stoi(config["ScreenWidth"]),
								   std::stoi(config["ScreenHeight"]), std::stoi(config["Fullscreen"]),
								   std::stoi(config["CoreMode"]), std::stoi(config["OpenGLScreen"]));

	Screen::Instance()->SetScreenColor(1.0f, 0.0f, 0.0f, 0.0f);

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

	m_renderer = new Renderer();

	m_isRunning = true;

	return true;
}

void App::Run()
{
	static bool isKeyPressed = false;

	Input::Instance()->Update();

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_O) && !isKeyPressed)
	{
		if (Screen::Instance()->IsOutlineMode())
		{
			Screen::Instance()->SetOutlineMode(false);
		}
		else
		{
			Screen::Instance()->SetOutlineMode(true);
		}
	}

	isKeyPressed = Input::Instance()->IsKeyPressed(SDL_SCANCODE_O);


	m_renderer->Update();
	m_renderer->Draw();
	
	m_isRunning = !(Input::Instance()->IsWindowClosed());
}

void App::Exit()
{
	//===========================
	// shutdown tasks
	//===========================
	Pipeline::Instance()->DetachShaders();
	Pipeline::Instance()->DestroyShaders();
	Pipeline::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	delete m_renderer;
	m_renderer = nullptr;
}

bool App::IsRunning()
{
	return m_isRunning;
}
