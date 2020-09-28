#include "Screen.h"
#include "Renderer.h"
#include "Input.h"
#include <iostream>

float deltaTime = 0.0f;
int lastTime = SDL_GetTicks();

int main(int argc, char* args[])
{

	Screen::Instance()->Initialize();
	Renderer* renderer = new Renderer();

	while (Screen::Instance()->IsRunning())
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();

		Input::Instance()->Update();

		Screen::Instance()->IsRunning() = !(Input::Instance()->IsXClicked());

		renderer->Update(deltaTime);
		renderer->Draw();

	}

	Screen::Instance()->Shutdown();

	return 0;
}