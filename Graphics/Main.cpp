#include "Input.h"
#include "Screen.h"
#include "Renderer.h"
#include "Utility.h"
#include "Pipeline.h"

#include <map>

float deltaTime = 0.0f;
int lastTime = SDL_GetTicks();
bool isEngineRunning = true;

int main(int argc, char* args[])
{
	std::string settings;
	std::map<std::string, std::string> configs;

	Utility::GetFileContents("Assets/Files/Settings.ini", settings);

	if (!settings.empty())
	{
		size_t sectionPos = settings.find("Basic");
		if (sectionPos != std::string::npos)
		{
			for (auto it = settings.begin(); it != settings.end(); it++)
			{
				//std::vector<std::string> tempConfig;
				//Utility::ParseString((*it), '=', tempConfig);

				//configs.insert({ tempConfig[0], tempConfig[1] });
			}
		}

	}

	Screen::Instance()->Initialize(configs["WindowTitle"], std::stoi(configs["ScreenWidth"]), 
								   std::stoi(configs["ScreenHeight"]), std::stoi(configs["Fullscreen"]),
								   std::stoi(configs["CoreMode"]), std::stoi(configs["OpenGLScreen"]));

	if (!Pipeline::Instance()->CreateProgram())
	{
		return 0;
	}

	if (!Pipeline::Instance()->CreateShaders())
	{
		return 0;
	}

	if (!Pipeline::Instance()->CompileShaders("Shaders/Main.vert"))
	{
		return 0;
	}

	Pipeline::Instance()->AttachShaders();

	if (!Pipeline::Instance()->LinkProgram())
	{
		return 0;
	}

	Renderer* renderer = new Renderer();

	while (isEngineRunning)
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();

		Input::Instance()->Update();

		isEngineRunning = !(Input::Instance()->IsWindowClosed());

		renderer->Update(deltaTime);
		renderer->Draw();
	}

	//===========================
	// shutdown tasks
	//===========================
	Pipeline::Instance()->DetachShaders();
	Pipeline::Instance()->DestroyShaders();
	Pipeline::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	return 0;
}