#include "Input.h"
#include "Screen.h"
#include "Renderer.h"
#include "Utility.h"

#include <map>
#include <iostream>


float deltaTime = 0.0f;
int lastTime = SDL_GetTicks();
bool isEngineRunning = true;

int main(int argc, char* args[])
{

	std::vector<std::string> readBuffer;
	std::map<std::string, std::string> m_configs;

	Utility::GetFileContents("Assets/Files/settings.ini", readBuffer);

	if (!readBuffer.empty())
	{
		for (auto it = readBuffer.begin(); it != readBuffer.end(); it++)
		{
			std::vector<std::string> tempConfig;
			Utility::ParseString((*it), '=', tempConfig);

			m_configs.insert({ tempConfig[0], tempConfig[1] });
		}
	}

	Screen::Instance()->Initialize(m_configs["WindowTitle"], std::stoi(m_configs["ScreenWidth"]), 
								   std::stoi(m_configs["ScreenHeight"]), std::stoi(m_configs["Fullscreen"]),
								   std::stoi(m_configs["CoreMode"]), std::stoi(m_configs["OpenGLScreen"]));

	Renderer* renderer = new Renderer();

	while (isEngineRunning)
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();

		Input::Instance()->Update();

		isEngineRunning = !(Input::Instance()->IsXClicked());

		renderer->Update(deltaTime);
		renderer->Draw();
	}

	Screen::Instance()->Shutdown();

	return 0;
}