#include "Screen.h"
#include "Renderer.h"
#include <iostream>

float deltaTime = 0.0f;
int lastTime = SDL_GetTicks();

int main(int argc, char* args[])
{

	Screen screen;
	Renderer* renderer = nullptr;;

	if (screen.Initialize())
	{
		renderer = new Renderer(screen.GetWindow());
	}

	while (screen.IsRunning())
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();

		//deltaTime = (deltaTime < 0.016f) ? 0.016f : deltaTime;
		std::cout << "DT: " << deltaTime << std::endl;

		renderer->Update(deltaTime);
		renderer->Draw();

	}

	screen.Shutdown();

	return 0;
}